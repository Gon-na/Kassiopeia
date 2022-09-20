#include "KEMCoreMessage.hh"
#include "KXMLInitializer.hh"
#include "KXMLTokenizer.hh"

#ifdef KEMFIELD_USE_PETSC
#include "KPETScInterface.hh"
#elif KEMFIELD_USE_MPI
#include "KMPIInterface.hh"
#endif

using namespace KEMField;
using namespace katrin;
using namespace std;

int main(int argc, char** argv)
{
    if (argc == 1) {
        std::cout
            << "usage: ./KEMField <config_file_one.xml> [<config_file_two.xml> <...>]"
            << " [ -v | -q ] [ -b | -batch ]"
            << " [ -r variable1=value1 variable2=value ... ] [ --variable3=value3 ... ]"
            << std::endl;
        exit(-1);
    }

#ifdef KEMFIELD_USE_PETSC
    KPETScInterface::GetInstance()->Initialize(&argc, &argv);
#elif KEMFIELD_USE_MPI
    KMPIInterface::GetInstance()->Initialize(&argc, &argv);
#endif

    auto& tXML = KXMLInitializer::GetInstance();
    auto* tTokenizer = tXML.Configure(argc, argv);  // process extra files below

    //tXML.DumpConfiguration();

    kem_cout(eNormal) << "starting..." << eom;

    auto tFileNames = tXML.GetArguments().ParameterList();
    tFileNames.pop_front();
    for (const auto& tFilename : tFileNames) {
        kem_cout(eNormal) << "processing file <" << tFilename << "> ..." << eom;
        auto* tFile = new KTextFile();
        tFile->AddToNames(tFilename);
        tTokenizer->ProcessFile(tFile);
        delete tFile;
    }

    kem_cout(eNormal) << "...finished" << eom;

    return 0;
}
