#include  "u_nm2m.hpp"
using namespace std;

// A global flag for debugging.
bool debugFlag = false;

int main(int argc, char* argv[]) {
  int opt;
  char  uInputFilename[BUFFSIZE] = "";
  char  uOutputFilename[BUFFSIZE] = "";

  // Arguments and command line options handling with getopt()
  // getopt() implicitly difines several variables.
  // optind: indicates the next index for the given argument.
  // optarg: contains the char * pointer to the arguments following the current
  // command line option.
  while((opt=getopt(argc, argv, "a:o:")) != -1) {
    switch(opt) {
    case 'a':
      cout << "Option specified: a " << optarg << " " << argv[optind++] << endl;
      cout << "This option is not yet implemented." << endl;
      break;
    case 'o':
      if(debugFlag) cout << "o: " << optarg << endl;
      strncpy(uOutputFilename, optarg, sizeof(uInputFilename)-1);
      break;
    case '?':
      if(debugFlag) cout << "Unknown option " << opt << " " << endl;
      dispHelp();
      break;
    }
  }
  if(debugFlag) cout << "argc: " << argc << ", " << "optind: " << optind << endl;
  if ((argc-optind) == 0) {
    cerr << "Specify the text vector field file." << endl << endl;
    dispHelp();
    return 1;
  }
  if ((argc-optind) > 1) {
    cerr << "Too many arguments." << endl << endl;
    dispHelp();
    return 1;
  }
  strncpy(uInputFilename, argv[optind], sizeof(uInputFilename)-1);
  if(debugFlag) cout << "text file: " << uInputFilename << endl;

  if (strcmp(uInputFilename, "")==0) strncpy(uInputFilename, DEFAULTUINPUTFILE, sizeof(uInputFilename)-1);
  // If the output binary filename is not specified, the following lines
  // copies the input text filename and changes the last part to "_m.ovf".
  if (strcmp(uOutputFilename, "")==0) {
    strncpy(uOutputFilename, uInputFilename, strlen(uInputFilename)-4);
    uOutputFilename[strlen(uOutputFilename)] = '\0';
    strcat(uOutputFilename, "_m.ovf");
  }

  if(debugFlag) cout << "u file: " << uOutputFilename << endl;

  // Construct the displacement vector field /////////////////////////
  std::ifstream fin(uInputFilename, ios::in);
  if(fin.fail()) {
    cerr << "File " << uInputFilename << " could not be opened." << endl;
    return 1;
  }
  VectorField ufield_nm(fin);
  fin.close();

  // Multiply the vector field by 1e-9 to convert displacement unit from nm to m
  int arraySize = ufield_nm.getsize();
  vector<pair<string,string> >  uheader = ufield_nm.getheader();
  double  ufield_m_array[arraySize][3]; // Displacement in meter
  for (int i=0; i<arraySize; i++) {
    ufield_m_array[i][0] = (1e-9)*ufield_nm.getx(i);
    ufield_m_array[i][1] = (1e-9)*ufield_nm.gety(i);
    ufield_m_array[i][2] = (1e-9)*ufield_nm.getz(i);
  }
  VectorField ufield_m(uheader, ufield_m_array);

  if(debugFlag) {
    cout << "Original ufield_nm." << endl;
    for (int i=0; i<10; i++)
      cout << ufield_nm.getx(i) << " " << ufield_nm.gety(i) << " " << ufield_nm.getz(i) << endl;
    cout << endl << "Converted ufield_m." << endl;
    for (int i=0; i<10; i++)
      cout << ufield_m.getx(i) << " " << ufield_m.gety(i) << " " << ufield_m.getz(i) << endl;
    cout << endl;
  }

  // =========================================================================
  // Write displacement to a binary file
  // =========================================================================
  if(debugFlag) cout << "Writing to a file in OVF 1.0 Binary 4 format." << endl;
  std::ofstream fout(uOutputFilename, ios::out);
  if(!fout) {
    cerr << "File " << uOutputFilename << " could not be opened." << endl;
    return 1;
  }
  ufield_m.writeVectorToFileB4(fout);
  fout.close();

  if(debugFlag) {
    ifstream fin2(uOutputFilename, ios::in);
    VectorField ufield_check(fin2);

    cout << endl << "Written file ufield_check." << endl;
    for (int i=0; i<10; i++)
      cout << ufield_check.getx(i) << " " << ufield_check.gety(i) << " " << ufield_check.getz(i) << endl;
  }

  return 0;
}

// Display help message
void dispHelp() {
  cout << "OOMMF OVF text-to-binary4 converter for displacement" << endl;
  cout << "This program converts the displacement in unit of nm to m" << endl;
  cout << "in order to modify the previous erroneous simulation outputs." << endl;
  cout << "Usage: u_t2b [-o OUTPUTFILENAME] INPUTFILENAME" << endl;
}
