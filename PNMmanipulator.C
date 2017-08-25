#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cerr;
using std::endl;
using std::ofstream;

int main(int argc, char *argv[])
{
    // Check arg len
    if (argc < 2 || argc > 3)
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        exit(EXIT_FAILURE);
    }
    

    // Log start
    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);

    // Initialize all objects
    PNMreader reader(argv[1]);  // note: filename must be "../images/image_name.pnm"
    Grayscale gs;
    Shrinker sr;
    Shrinker sr2;
    Shrinker sr3;
    Shrinker sr4;
    TBConcat tb;
    TBConcat tb2;
    LRConcat lr;
    LRConcat lr2;
    Mirror mr;

    // Set inputs and outputs
    sr.SetInput(reader.GetOutput());
    sr2.SetInput(sr.GetOutput());
    sr3.SetInput(sr2.GetOutput());
    
    gs.SetInput(sr3.GetOutput());

    lr.SetInput(sr3.GetOutput());
    lr.SetInput2(gs.GetOutput());

    mr.SetInput(lr.GetOutput());

    tb.SetInput(mr.GetOutput());
    tb.SetInput2(lr.GetOutput());

    lr2.SetInput(tb.GetOutput());
    lr2.SetInput2(tb.GetOutput());

    tb2.SetInput(lr2.GetOutput());
    tb2.SetInput2(lr2.GetOutput());

    // set final output 
    Image *finalImage = tb2.GetOutput();

    // execute pipeline and catch exceptions
    try
    {
        finalImage->Update();
    }
    catch (DataFlowException &)
    {
        ofstream ofile("my_exception");
        if (ofile.fail())
        {
             cerr << "Something is wrong ... can't open my_exception"
                  << " for opening" << endl;
             exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }

    // Output checksum
    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("Image_Checksum");

    // Output image
    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("OutputImage.pnm");
    }
    // output log file
    Logger::Finalize();
}
