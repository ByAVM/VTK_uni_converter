#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <chrono>

#include "ConfigReader.h"

#include "factory/ConverterFactory.h"

#include "reader/SequenceReader.h"
#include "reader/SingleReader.h"
#include "adapter/StructuredGridAdapter.h"
#include "adapter/UnstructuredGridAdapter.h"
#include "converter/GrdConverter.h"
#include "converter/CustomConverter.h"
#include "converter/CustomConverter1.h"
#include "converter/PointStructureConverter.h"

using namespace std;
using namespace vtkConv;
namespace fs = experimental::filesystem;

void initReaderFactory(shared_ptr<ReaderFactory>& factory)
{
    factory->add<SingleReader>("single");
    factory->add<SequenceReader>("sequence");
}

void initAdapterFactory(shared_ptr<AdapterFactory>& factory)
{
    factory->add<StructuredGridAdapter>("structured_grid");
    factory->add<UnstructuredGridAdapter>("unstructured_grid");
}

void initConverterFactory(shared_ptr<ConverterFactory>& factory)
{
    factory->add<CustomConverter>("custom");
    factory->add<CustomConverter1>("custom1");
    factory->add<PointStructureConverter>("point_structure");
    factory->add<GrdConverter>("surfer6_grd");
}

int main(int nargs, char * args)
{
    // vector<string> cmdArgs(&args[0], &args[0 + nargs]);

    if (nargs < 1) {
        cout << "Use [path/to/config]" << endl;
        return 1;
    }

    string pathArg(&args[1]);
    // fs::path config_path(pathArg);

    fs::path config_path("D:\\Workflow\\ВКР\\Программа\\GrdConfig.json");
    // fs::path config_path("D:\\Workflow\\ВКР\\Программа\\CustomConfig.json");
    // fs::path config_path("D:\\Workflow\\ВКР\\Программа\\PSConfig.json");

    if (!fs::exists(config_path)) 
    {
        cout << "Config File not found in: " + config_path.string() << endl;
        return 1;
    }

    shared_ptr<ConverterFactory> cf = make_shared<ConverterFactory>();
    shared_ptr<ReaderFactory> rf = make_shared<ReaderFactory>();
    shared_ptr<AdapterFactory> af = make_shared<AdapterFactory>();

    initAdapterFactory(af);
    initReaderFactory(rf);
    initConverterFactory(cf);

    ConfigReader config_reader(cf, af, rf);

    cout << "Init complete" << endl;
    try
    {
        config_reader.readConfig(config_path.string());
    } catch(exception& exept) {
        cout << exept.what() << endl;
        return 1;
    }


    unique_ptr<IConverter> converter = config_reader.getConverter(); /// Converter already initialized
    
    fs::directory_iterator input_files(config_reader.getInput());
    
    fs::path output_dir(config_reader.getOutput());

    auto all_start = chrono::system_clock::now();
    for (const fs::directory_entry& input_file_path : input_files)
    {
        cout << "Converting: " << input_file_path.path() << ".." << endl;
        auto one_start = chrono::system_clock::now();
        try
        {
            converter->convertFile(input_file_path.path().string())
                ->writeFile((output_dir / input_file_path.path().stem()).string());
            cout << " Done" << endl;
        } catch(exception& exept) {
            cout << exept.what() << endl;
        }
        auto one_end = chrono::system_clock::now();
        chrono::duration<double> elapsed = one_end - one_start;
        cout << "Time:" << elapsed.count() << endl;
        // break;
    }
    auto all_end = chrono::system_clock::now();
    chrono::duration<double> elapsed = all_end - all_start;
    cout << "All time:" << elapsed.count() << endl;

    return 0;
}