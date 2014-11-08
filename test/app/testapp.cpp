/*
 * testapp.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: romeo
 */
#include <iostream>

#include "cpp-instagram/Instagram.h"

#include<boost/program_options.hpp>

using namespace Instagram;
using namespace std;

void downloadImages(string client_id, string tag) {
	try {
		ClientPtr client = CreateClient(client_id);

		cout << "Connecting to Instagram with client-id " << client_id << endl;


		MediaList medias;
		if(!tag.empty()){
			cout << "Searching for recent images for tag " << tag << endl;
			medias = client->getRecentMediasByTag(tag);
		}else{
			medias = client->getPopularMedias();
			cout << "Searching for recent popular images" << endl;
		}

		cout << "Found " << medias.size() << " photos" << endl;
		for (MediaPtr media : medias) {
			const string id = media->getId();
			cout << "Downloading image with id" << id << endl;
			media->getImages()->getStandardResolution()->download(id + ".jpg");
		}
	} catch (const Exception& e) {
		cerr << "Exception raised: " << e.getMessage() << endl;
	}
}

int main(int argc, char **argv) {

	namespace po = boost::program_options;
	po::options_description desc("Allowed options");
	desc.add_options()
			("help", "describe arguments")
			("client-id", po::value<string>(), "Client id for user app")
			("tag", po::value<string>(), "tag to search");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << endl;
		return 1;
	}

	if (!vm.count("client-id")) {
		std::cerr << "token is not set!\n";
		cout << desc << endl;
		return 1;
	}

	string token = vm["client-id"].as<string>();
	string tag = vm["tag"].as<string>();

	downloadImages(token, tag);

}

