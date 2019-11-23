#include "Blockchain.h"
#include "Network.h"

int main()
{
	try
	{
		boost::asio::io_service io_service;
		network::sender s(io_service, boost::asio::ip::address::from_string("239.255.0.1"));
		io_service.run();

		Blockchain bChain = Blockchain();

		cout << "Mining block 1..." << endl;
		bChain.AddBlock(Block(1, "Block 1 Data"));

		cout << "Mining block 2..." << endl;
		bChain.AddBlock(Block(2, "Block 2 Data"));

		cout << "Mining block 3..." << endl;
		bChain.AddBlock(Block(3, "Block 3 Data"));
	}
	catch (std::exception & e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
