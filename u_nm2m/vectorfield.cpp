#include  "u_nm2m.hpp"
#include  "vectorfield.hpp"
using namespace std;

// For searching for a key in the header items
template <typename T, typename U>
struct first_equals {
  typedef T first_argument_type;
  typedef pair<T,U> second_argument_type;
  typedef bool result_type;
  bool operator() (const T& v, pair<T,U>& p) const {
       return p.first == v;
  }
};

//////////////////////////////////////////////////////////////////////
// Constructors
//////////////////////////////////////////////////////////////////////
VectorField::VectorField(ifstream& ifs) {
  Vector3d  tempvec;
  char  buff[BUFFSIZE];
  string  sbuff;
  string  headerItem[2];
  //map<string, string> header;

  // Read the header /////////////////////////////////////////////////
  do {
    ifs.getline(buff, sizeof(buff));
    sbuff = buff;
    readOhfHeaderItem(sbuff, headerItem);
    header.push_back(pair<string,string>(
          headerItem[0], headerItem[1]
          ));
  } while(!(headerItem[0] == "End" && headerItem[1] == "Header"));

  vector<pair<string,string> >::iterator vitr;
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "xnodes")); xnodes = toInt(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "ynodes")); ynodes = toInt(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "znodes")); znodes = toInt(vitr->second);
  size = xnodes*ynodes*znodes;
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "xstepsize")); xstepsize = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "ystepsize")); ystepsize = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "zstepsize")); zstepsize = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "xbase")); xbase = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "ybase")); ybase = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "zbase")); zbase = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "valuemultiplier")); valuemultiplier = toDouble(vitr->second);

  vec.reserve(size);

  // Record the data length //////////////////////////////////////////
  ifs.getline(buff, sizeof(buff));
  sbuff = buff;
  readOhfHeaderItem(sbuff, headerItem);
  binarysize = 0;

  // For Binary 4 format
  if (headerItem[1] == "Data Binary 4") {
    binarysize = 4;
    float f[3];
    // Read the check value and record the vector field. ///////////////
    ifs.read( (char*)& f[0], sizeof(f[0]));
    bswap(f[0]); // Byte order conversion
    if (f[0] == 1234567.0) {
      if(debugFlag) cerr << "Check value correct." << endl;
    } else {
      cerr << "Check value incorrect." << endl;
    }

    for(int i=0; i<size; i++) {
      for(int j=0; j<3; j++) {
        ifs.read( (char*)& f[j], sizeof(f[0]));
        bswap(f[j]);
      }
      tempvec.put(f[0], f[1], f[2]);
      vec.push_back(tempvec);
    }
  }

  // For Binary 8 format
  if (headerItem[1] == "Data Binary 8") {
    binarysize = 8;
    double f[3];
    // Read the check value and record the vector field. ///////////////
    ifs.read( (char*)& f[0], sizeof(f[0]));
    bswap(f[0]); // Byte order conversion
    if (f[0] == 123456789012345.0) {
      if(debugFlag) cerr << "Check value correct." << endl;
    } else {
      cerr << "Check value incorrect." << endl;
    }

    for(int i=0; i<size; i++) {
      for(int j=0; j<3; j++) {
        ifs.read( (char*)& f[j], sizeof(f[0]));
        bswap(f[j]);
      }
      tempvec.put(f[0], f[1], f[2]);
      vec.push_back(tempvec);
    }
  }

  // For text format
  if (headerItem[1] == "Data Text") {
    binarysize = 8;
    double f[3];

    for(int i=0; i<size; i++) {
      getline(ifs, sbuff);
      sscanf(sbuff.data(), "%le %le %le", &f[0], &f[1], &f[2]);
      tempvec.put(f[0], f[1], f[2]);
      vec.push_back(tempvec);
    }
  }
}

// Constructor 2 - copy from header vector and double array
VectorField::VectorField(const std::vector<std::pair<std::string,std::string> > inheader, const double infield[][3]) {
  Vector3d  tempvec;
  char  buff[BUFFSIZE];
  string  sbuff;
  string  headerItem[2];

  // Copy the header /////////////////////////////////////////////////
  header = inheader;

  vector<pair<string,string> >::iterator vitr;
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "xnodes")); xnodes = toInt(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "ynodes")); ynodes = toInt(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "znodes")); znodes = toInt(vitr->second);
  size = xnodes*ynodes*znodes;
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "xstepsize")); xstepsize = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "ystepsize")); ystepsize = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "zstepsize")); zstepsize = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "xbase")); xbase = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "ybase")); ybase = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "zbase")); zbase = toDouble(vitr->second);
  vitr = find_if(header.begin(), header.end(), bind1st(first_equals<string,string>(), "valuemultiplier")); valuemultiplier = toDouble(vitr->second);

  vec.reserve(size);

  for(int i=0; i<size; i++) {
    vec.push_back(Vector3d(infield[i][0], infield[i][1], infield[i][2]));
  }
}

// Copy constructor
VectorField::VectorField(const VectorField& input) {
  Vector3d  tempvec;
  char  buff[BUFFSIZE];
  string  sbuff;
  string  headerItem[2];

  header = input.header;
  xnodes = input.xnodes;
  ynodes = input.ynodes;
  znodes = input.znodes;
  size = xnodes*ynodes*znodes;
  xstepsize = input.xstepsize;
  ystepsize = input.ystepsize;
  zstepsize = input.zstepsize;
  xbase = input.xbase;
  ybase = input.ybase;
  zbase = input.zbase;
  valuemultiplier = input.valuemultiplier;
  binarysize = input.binarysize;

  vec.reserve(size);

  for(int i=0; i<size; i++) {
    vec.push_back(input.vec[i]);
  }
}

void VectorField::writeVectorToFileB4(ofstream& ofs) {
  float f;  // Data Binary 4
  f = 1234567.0;  // Check value for Data Binary 4
  bswap(f); // Byte order conversion

  vector<pair<string,string> >::iterator vitr = header.begin();
  while(vitr != header.end()) {
    ofs << "# " << vitr->first << ": " << vitr->second << endl;
    vitr++;
  }
  ofs << "# Begin: Data Binary 4" << endl;
  ofs.write((char *) &f, sizeof(f));
  for(int i=0; i<size; i++) {
    f = vec[i].getx();
    bswap(f);
    ofs.write((char *) &f, sizeof(f));
    f = vec[i].gety();
    bswap(f);
    ofs.write((char *) &f, sizeof(f));
    f = vec[i].getz();
    bswap(f);
    ofs.write((char *) &f, sizeof(f));
  }
  ofs << endl << "# End: Data Binary 4" << endl << "# End: Segment";
}

void VectorField::writeVectorToFileB8(ofstream& ofs) {
  double f;  // Data Binary 8
  f = 123456789012345.0;  // Check value for Data Binary 8
  bswap(f); // Byte order conversion

  vector<pair<string,string> >::iterator vitr = header.begin();
  while(vitr != header.end()) {
    ofs << "# " << vitr->first << ": " << vitr->second << endl;
    vitr++;
  }
  ofs << "# Begin: Data Binary 8" << endl;
  ofs.write((char *) &f, sizeof(f));
  for(int i=0; i<size; i++) {
    f = vec[i].getx();
    bswap(f);
    ofs.write((char *) &f, sizeof(f));
    f = vec[i].gety();
    bswap(f);
    ofs.write((char *) &f, sizeof(f));
    f = vec[i].getz();
    bswap(f);
    ofs.write((char *) &f, sizeof(f));
  }
  ofs << endl << "# End: Data Binary 8" << endl << "# End: Segment";
}

vector<bool> VectorField::getmask() {
  vector<bool>  out;
  for (int i=0; i<size; i++) {
    if (vec[i].getsq() == 0.0) out.push_back(false);
    else out.push_back(true);
  }
  return out;
}
    
int VectorField::readOhfHeaderItem(string& s, string* item) {
  string  ret[2];
  int n1, n2;
  n1 = s.find_first_not_of("# ");
  n2 = s.find_first_of(":");
  item[0] = s.substr(n1, n2-n1);
  item[1] = s.substr(n2+2);
  item = ret;
}

