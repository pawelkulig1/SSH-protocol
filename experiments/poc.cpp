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
	auto recv = sc.recv();
	sc.send(Host::payload_from_hex(
				"000002340614f655be72054e57a48c444cd3e60167820000002f6469666669652d68656c6c6d616e2d67726f75702d65786368616e67652d7368613235362c6578742d696e666f2d630000016665636473612d736861322d6e697374703235362d636572742d763031406f70656e7373682e636f6d2c65636473612d736861322d6e697374703338342d636572742d763031406f70656e7373682e636f6d2c65636473612d736861322d6e697374703532312d636572742d763031406f70656e7373682e636f6d2c65636473612d736861322d6e697374703235362c65636473612d736861322d6e697374703338342c65636473612d736861322d6e697374703532312c7373682d656432353531392d636572742d763031406f70656e7373682e636f6d2c7273612d736861322d3531322d636572742d763031406f70656e7373682e636f6d2c7273612d736861322d3235362d636572742d763031406f70656e7373682e636f6d2c7373682d7273612d636572742d763031406f70656e7373682e636f6d2c7373682d656432353531392c7273612d736861322d3531322c7273612d736861322d3235362c7373682d7273610000000a6165733132382d6374720000000a6165733132382d63747200000009686d61632d7368613100000009686d61632d736861310000001a6e6f6e652c7a6c6962406f70656e7373682e636f6d2c7a6c69620000001a6e6f6e652c7a6c6962406f70656e7373682e636f6d2c7a6c696200000000000000000000000000000000000000"
				));
	recv = sc.recv();
	
	sc.send(Host::payload_from_hex(
			"0000001406220000080000001e0000002000000000000000"	
				));

	recv = sc.recv();
	
	std::string rcv = Host::vector_to_string(recv);
	std::string modulus = rcv.substr(20, 961*2);
	std::string base = rcv.substr(20 + 961*2 + 8, 2 );

	/*for(int i=0;i<modulus.size();i++)
	{
		std::cout<<std::hex << std::setfill('0') << static_cast<int16_t>(modulus[i]) << "";
		if(i % 2 == 0) std::cout<< " ";
		if(i % 16 == 0) std::cout<< "  ";
		if(i % 32 == 0) std::cout<< std::endl;
	}
	std::cout<<std::endl;*/
	std::vector<Byte> modulus_vec;
	for(int i=0;i<modulus.size();i+=2)
	{
		modulus_vec.push_back(Byte(modulus[i], modulus[i+1]));
	}

	std::vector<Byte> base_vec;
	base_vec.push_back(Byte(base[0], base[1]));
	
	BigNum p, g;
	p = modulus_vec;
	g = base_vec;	
	DiffieHellman dh1;
	dh1.set_p(p);
	dh1.set_g(g);
	dh1.generate_keys();
	BigNum pub_key = dh1.get_pub();

	std::vector<Byte> pub = pub_key.get();
	/*std::string e(pub);
	e = "00" + e;
	std::cout<<"e0"<<(int)(e[0])<<std::endl;
	
	*/
	std::string e;
	for(const Byte byte: pub)
	{
		e += byte.get_str();
	}
	//std::cout<<"E: " << e<<"pub.size(): " <<pub.size() <<std::endl;
	std::string payload = "000003cc"
	"05"
	"20"
	"000003c1"
	"00"
	+e+
	"0000000000";
	//std::cout<<"payload size: " << payload.size()<<" " << e.size() <<std::endl;
	sc.send(Host::payload_from_hex(payload));
	
	recv = sc.recv();
	rcv = Host::vector_to_string(recv);
	std::string f = rcv.substr(118*2, 961*2);

	std::vector<Byte> f_vec;
	for(int i=0;i<f.size();i+=2)
	{
		f_vec.push_back(Byte(f[i], f[i+1]));
	}
	BigNum f_b, K;
	f_b = f_vec;
	DiffieHellman dh2;
	dh2.set_p(p);
	dh2.set_g(f_b);
	BigNum priv = dh1.get_priv();
	dh2.set_priv(priv);
	dh2.generate_keys();
	K = dh2.get_pub();
	std::cout<<K<<std::endl;






	
	sc.send(Host::payload_from_hex(
			"0000000c0a1500000000000000000000"	
				));


	//recv = sc.recv();


	
	
	
	

	//"008f9457461e9d4e76bd9fa255ed75978817c84767907ec5afb1b18e5b44e9e0a883b79b58f79edc7f00f865af4747a24182c0719b713c78544dc0c355de3d82572246cf1a9002a3bf4cfccc108bf2049e671be0e4722f9a679cbbc1c57d43c0794a18da2664a4c7b28a382cf713c240984767308a34d1584662f09ff499992feecc100165f1fea82cc12ccd8aa10a1f1a1bd519f5c1a652305c0a7380ec5ad6a7ffcc3532c47d44fdbe633a4d66a935b9fa76fb4e75116ebbbaa6d728b4e979922ae4c04795f2cba56e7a3e272dd35630d878a591cc5391090be432b8ea364cc79d3874afe0ecb34d7e43cbdc9f47f192064fc23bbe15e848de6dd921a9aae53cb9a16936dfb565344fb222ffd25a5e82d371b2f3114e5e1eb0ddb9aec3e62424aa64816caf450371cd4f473b0115832575070d6b222689c82d7f3af7809fc8b75e5a50160270e39b75f325e8d6d2e17264bc5f4d699dcade290c5337c59b710a4061f731ebffffce2d06afb8874ebc77ad436666f26cd0e59c9a3ffc32cfebf645711c641ee621ed5efd368042267e9c861925e6f26e08ca7a6aea51b49bb1786a524fd0cbc2eb569ad2a9c38e91b22be269a1d687d929fbd7ef03512845ba633fef0c21ab9f1a069ed113f454f23af4088a550e3efa4978a2cd2f8e468c3469d18ccd083a498d8b238a8124c242361a81cee92cb1e82f4135d39d306f209b32474f1477239a77dac1a65fa2937faf79298d005967e8b5e5039980d442203387e63de609e5f7cc4803a67f8d1f5969759dcb22d4e0df0f02418105439907f30027b714fef6972d3e90c08c2213c342cf874cd47ac57c2cc73abd5eb862c2e2c6cb458983910d911f53fdac7ae3e38e63d7cdc473217ffe348d7ea9a320a71f7a34b903ad1abfe2a17acfaf1851666b17670c43c9a5300e7c48f9af91aada606f6940e23592204756fac983c96c78ca817863b88b334ac613d2067786819a1ae65371068c137e3bb3abf3fc08188c3acb9ffb72f1f42aca2769da61aebfa9535f8c7b5712e680779b3bfdddada0ecf916049f2d3d0fb3b1ba16e11fac858bce9d9efdf2eb5054b2cd06b7ef50121833d891e63b529996072d0a4a719e611ef4b6ea66b9905351eea6c179d0ccff79ef45548276deb7dcaa54faf8600e9f4ca33952672d98fa8e5fe2e2e6cbc1a371440f6fcf9fbb09c52f81ab3de0cc5d374830e29dc1e441f72059c572f192e55f61f8df6891d0bfa99a57039202d8ce4d90af4aa6f4781410f03872c794ecfb05179d0328c9c299c5140dac38ac4d0bd36494d0db58be89cc56cdebd1184e902ecebf0f51825595b98260f229a58e43479b63"

	/*int pub_size = BN_num_bytes(pub_key);
	const char *pub = new char[pub_size];
	pub = BN_bn2hex(pub_key);*/

	/*for(int i=0;i<pub_size;i++)
	{
		std::cout<<std::hex<<std::setfill('0')<<static_cast<int>(pub[i]) << " ";
		if(i%8 == 0 && i%16 != 0) std::cout<<"  ";
		if(i%16 == 0) std::cout<<std::endl;
	}*/
	//std::cout<<std::endl;



	//BIGNUM *priv_key = dh->priv_key;


	

    return 0;
}
