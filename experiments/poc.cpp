#include <iostream>
#include <iomanip>
#include "../socket_sources/socket_class.h"
#include "../host.h"
#include "../ssh_packets/protocol_exchange.h"
#include "../ssh_packets/key_exchange_init.h"
#include <unistd.h>
#include <openssl/bn.h>
#include <openssl/dh.h>
#include <openssl/err.h>
#include "../encryption/big_num.h"
#include "../encryption/dh.h"



int main()
{
	using SSH::BigNum;
	using SSH::DiffieHellman;
    SocketClass sc("0.0.0.0", 22);
	sc.connect();
	sc.send(protocol_exchange.getFrame());
	auto server_protocol = sc.recv();
	auto client_kex = Host::payload_from_hex("000002340614f655be72054e57a48c444cd3e60167820000002f6469666669652d68656c6c6d616e2d67726f75702d65786368616e67652d7368613235362c6578742d696e666f2d630000016665636473612d736861322d6e697374703235362d636572742d763031406f70656e7373682e636f6d2c65636473612d736861322d6e697374703338342d636572742d763031406f70656e7373682e636f6d2c65636473612d736861322d6e697374703532312d636572742d763031406f70656e7373682e636f6d2c65636473612d736861322d6e697374703235362c65636473612d736861322d6e697374703338342c65636473612d736861322d6e697374703532312c7373682d656432353531392d636572742d763031406f70656e7373682e636f6d2c7273612d736861322d3531322d636572742d763031406f70656e7373682e636f6d2c7273612d736861322d3235362d636572742d763031406f70656e7373682e636f6d2c7373682d7273612d636572742d763031406f70656e7373682e636f6d2c7373682d656432353531392c7273612d736861322d3531322c7273612d736861322d3235362c7373682d7273610000000a6165733132382d6374720000000a6165733132382d63747200000009686d61632d7368613100000009686d61632d736861310000001a6e6f6e652c7a6c6962406f70656e7373682e636f6d2c7a6c69620000001a6e6f6e652c7a6c6962406f70656e7373682e636f6d2c7a6c696200000000000000000000000000000000000000");
	sc.send(client_kex);
	auto server_kex = sc.recv();
	
	//group exchange request
	sc.send(Host::payload_from_hex(
			"0000001406220000080000001e0000002000000000000000"	
				));

	auto server_group_exchange = sc.recv();
	
	auto modulus = server_group_exchange.get(20, 961*2);
	auto base = server_group_exchange.get(20 + 961 * 2 + 8, 2);
	//auto rcv = Host::vector_to_string(recv);
	//std::string modulus = rcv.substr(20, 961*2);
	//std::string base = rcv.substr(20 + 961*2 + 8, 2 );

	/*for(int i=0;i<modulus.size();i++)
	{
		std::cout<<std::hex << std::setfill('0') << static_cast<int16_t>(modulus[i]) << "";
		if(i % 2 == 0) std::cout<< " ";
		if(i % 16 == 0) std::cout<< "  ";
		if(i % 32 == 0) std::cout<< std::endl;
	}
	std::cout<<std::endl;*/
	/*std::vector<Byte> modulus_vec;
	for(int i=0;i<modulus.size();i+=2)
	{
		modulus_vec.push_back(Byte(modulus[i], modulus[i+1]));
	}*/

	//std::vector<Byte> base_vec;
	//base_vec.push_back(Byte(base[0], base[1]));
	
	BigNum p, g;
	p = modulus;//modulus_vec;
	g = base;//base_vec;	
	DiffieHellman dh1;
	dh1.set_p(p);
	dh1.set_g(g);
	dh1.generate_keys();
	BigNum client_pub = dh1.get_pub();

	//Payload pub = pub_key.get();
	/*std::string e(pub);
	e = "00" + e;
	std::cout<<"e0"<<(int)(e[0])<<std::endl;
	
	*/
	std::string e;
	for(const Byte byte: client_pub.get())
	{
		e += byte.get_str();
	}
	//std::cout<<"E: " << e<<"pub.size(): " <<pub.size() <<std::endl;
	//group_exchange_init
	std::string payload = "000003cc"
	"05"
	"20"
	"000003c1"
	"00"
	+e+
	"0000000000";
	//std::cout<<"payload size: " << payload.size()<<" " << e.size() <<std::endl;
	sc.send(Host::payload_from_hex(payload));
	
	auto group_exchange_reply = sc.recv();
	//rcv = Host::vector_to_string(recv);
	//std::string f = rcv.substr(118*2, 961*2);
	auto server_dh_rsa_modulus = group_exchange_reply.get(10, 20);
	auto f = group_exchange_reply.get(118*2, 961*2);
	//std::vector<Byte> f_vec;
	//for(int i=0;i<f.size();i+=2)
	//{
	//	f_vec.push_back(Byte(f[i], f[i+1]));
	//}
	BigNum server_pub, K;
	server_pub = f;
	DiffieHellman dh2;
	dh2.set_p(p);
	dh2.set_g(server_pub);
	BigNum client_priv = dh1.get_priv();
	dh2.set_priv(client_priv);
	dh2.generate_keys();
	K = dh2.get_pub();
	std::cout<<K<<std::endl;

	Payload h = Payload();
	h.next(protocol_exchange.getFrame());
	h.next(server_protocol);
	//p.next(client_kex.size(), 4);
	//p.next(SSH_OPCODES::SSH_MSG_KEXINIT, 1);
	h.next(client_kex);
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








	
	sc.send(Host::payload_from_hex(
			"0000000c0a1500000000000000000000"	
				));
}
