//#include <iostream>
//#include <iomanip>
//#include "../socket_sources/socket_class.h"
//#include "../host.h"
//#include "../ssh_packets/protocol_exchange.h"
//#include "../ssh_packets/key_exchange_init.h"
//#include <unistd.h>
//#include <openssl/bn.h>
//#include <openssl/dh.h>
//#include <openssl/err.h>
//#include "../encryption/big_num.h"
//#include "../encryption/dh.h"



int main()
{
	return 0;
	//using SSH::BigNum;
	//using SSH::DiffieHellman;
    //SocketClass sc("0.0.0.0", 22);
	//sc.connect();

	//sc.send(protocol_exchange.getFrame());
	//auto server_protocol = sc.recv();
	//std::cout<<"start"<<std::endl;
	//auto client_kex = key_exchange_init;
	//std::cout<<"start2"<<std::endl;
	//auto client_kex = Host::payload_from_hex("000000d405142905c34ae41af225d2e55583a2ebf2ee0000002f6469666669652d68656c6c6d616e2d67726f75702d65786368616e67652d7368613235362c6578742d696e666f2d63000000077373682d7273610000000a6165733132382d6374720000000a6165733132382d63747200000009686d61632d7368613100000009686d61632d736861310000001a6e6f6e652c7a6c6962406f70656e7373682e636f6d2c7a6c69620000001a6e6f6e652c7a6c6962406f70656e7373682e636f6d2c7a6c6962000000000000000000000000000000000000");
	//std::cout<<client_kex.getFrame().get_str()<<std::endl;
	/*sc.send(client_kex.getFrame());
	auto server_kex = sc.recv();
	
	//group exchange request
	sc.send(Host::payload_from_hex(
			"0000001406220000080000001e0000002000000000000000"	
				));

	auto server_group_exchange = sc.recv();
	
	auto modulus = server_group_exchange.get(10, 1025);
	std::cout<< "modulus: "<< modulus.get_str()<<std::endl;
	auto base = server_group_exchange.get(10 + 1025 + 4, 1);
	std::cout<< "base: " << base.get_str()<<std::endl;

	BigNum p, g;
	p = modulus;//modulus_vec;
	g = base;//base_vec;	
	DiffieHellman dh1;
	dh1.set_p(p);
	dh1.set_g(g);
	dh1.generate_keys();
	BigNum client_pub = dh1.get_pub();

	std::string e = client_pub.get().get_str();
	std::cout<<"E: " << e << std::endl;
	std::string payload = "000003cc"
	"05"
	"20"
	"000003c1"
	"00"
	+e+
	"0000000000";
	sc.send(Host::payload_from_hex(payload));
	
	auto group_exchange_reply = sc.recv();
	auto server_dh_rsa_modulus = group_exchange_reply.get(32, 385);
	auto f = group_exchange_reply.get(421, 961);
	std::cout << "server_dh_rsa_modulus: " << server_dh_rsa_modulus.get_str() << std::endl;
	std::cout << "F: " << f.get_str() << std::endl;

	BigNum server_pub, K;
	server_pub = f;
	DiffieHellman dh2;
	dh2.set_p(p);
	dh2.set_g(server_pub);
	BigNum client_priv = dh1.get_priv();
	dh2.set_priv(client_priv);
	dh2.generate_keys();
	K = dh2.get_pub();

	Payload h = Payload();
	h.next("00000015"); //payload size
	h.next(protocol_exchange.getPayload());
	h.next("00000013"); // payload size
	h.next(server_protocol.get(0, server_protocol.size() - 2));
	//p.next(client_kex.size(), 4);
	//p.next(SSH_OPCODES::SSH_MSG_KEXINIT, 1);
	h.next(client_kex.getPayload());
	h.next(server_kex);
	h.next(server_dh_rsa_modulus);
	h.next(2048, 4);
	h.next(7680, 4);
	h.next(8192, 4);
	h.next(p.get());
	h.next(g.get());
	h.next(client_pub.get());
	h.next(server_pub.get());
	h.next(K.get());
	h.print();

	
	sc.send(Host::payload_from_hex(
			"0000000c0a1500000000000000000000"	
				));
	*/
}
