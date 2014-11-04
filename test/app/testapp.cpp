/*
 * testapp.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: romeo
 */
#include <iostream>

#include "cpp-instagram/AuthenticatedClient.h"
#include "cpp-instagram/Exception.h"

#include<boost/program_options.hpp>

using namespace Instagram;
using namespace std;

void downloadPopularImages(string token)
{
    try
    {
        ClientPtr client = CreateClient(token);

        MediaList medias = client->getPopularMedias();

        for (MediaPtr media : medias)
        {
            const std::string id = media->getId();
            media->getImages()->getStandardResolution()->download(id + ".jpg");
        }
    }
    catch (const Exception& e)
    {
        std::cerr << "Exception raised: " << e.getMessage() << std::endl;
    }
}

int main(int argc, char **argv){

	namespace po = boost::program_options;
	po::options_description desc("Allowed options");
	desc.add_options()
	("help", "describe arguments")
	("token", po::value<string>(), "token");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
	cout << desc << "\n";
	return 1;
	}

	if (vm.count("token")) {
		cout << "Token is " << vm["token"].as<string>() << ".\n";
		downloadPopularImages(vm["token"].as<string>());
	} else {
		cout << "token is not set!\n";
	}

}

