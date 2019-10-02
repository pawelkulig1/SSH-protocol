#include <iostream>
#include <iomanip>
#include "socket_sources/socket_class.h"
#include "host.h"
#include "ssh_packets/protocol_exchange.h"
#include "ssh_packets/key_exchange_init.h"
#include <unistd.h>
#include <openssl/bn.h>
#include <openssl/dh.h>
#include <openssl/err.h>



int main()
{
    SocketClass sc("0.0.0.0", 22);
	sc.connect();
	sc.send(protocol_exchange.getFrame());
	auto server_protocol_name = sc.recv();
	// Frame frame;
	// frame = recv;
	// frame.parse();
	//sc.send(key_exchange_init.getFrame());
	sc.send(Host::payload_from_hex(
				"000002340614f655be72054e57a48c444cd3e60167820000002f6469666669652d68656c6c6d616e2d67726f75702d65786368616e67652d7368613235362c6578742d696e666f2d630000016665636473612d736861322d6e697374703235362d636572742d763031406f70656e7373682e636f6d2c65636473612d736861322d6e697374703338342d636572742d763031406f70656e7373682e636f6d2c65636473612d736861322d6e697374703532312d636572742d763031406f70656e7373682e636f6d2c65636473612d736861322d6e697374703235362c65636473612d736861322d6e697374703338342c65636473612d736861322d6e697374703532312c7373682d656432353531392d636572742d763031406f70656e7373682e636f6d2c7273612d736861322d3531322d636572742d763031406f70656e7373682e636f6d2c7273612d736861322d3235362d636572742d763031406f70656e7373682e636f6d2c7373682d7273612d636572742d763031406f70656e7373682e636f6d2c7373682d656432353531392c7273612d736861322d3531322c7273612d736861322d3235362c7373682d7273610000000a6165733132382d6374720000000a6165733132382d63747200000009686d61632d7368613100000009686d61632d736861310000001a6e6f6e652c7a6c6962406f70656e7373682e636f6d2c7a6c69620000001a6e6f6e652c7a6c6962406f70656e7373682e636f6d2c7a6c696200000000000000000000000000000000000000"
				));
	auto server_kex = sc.recv();
	
	//KEXProtocolPicker kpp;
	//KEXProtocol kex_protocol;
	//kex_protocol = kp.pick_protocol(key_exchange_init.getFrame(), recv);
	

	//sc.send(kex_protocol.key_exchange_request().getFrame());
	sc.send(Host::payload_from_hex(
			"0000001406220000080000001e0000002000000000000000"	
				));

	auto recv = sc.recv();
	
	std::string rcv = Host::vector_to_string(recv);
	std::string modulus = rcv.substr(20, 961*2);
	std::string base = rcv.substr(20 + 961*2 + 8, 2 );

	//frame server_keys(recv);
	//server_keys.parse();
	//SSH::BigNum p, g, pub_key, priv_key;
	//p = server_keys.get_p();
	//g = server_keys.get_g();
	//
	//SSH::DH dh;
	//dh.set_p(p);
	//dh.set_g(g);
	//
	//frame group_exchange_init;
	//group_exchange_init.e = dh.get_pub();
	//sc.send(group_exchange_init.get_frame());
	//
	//
	//
	BIGNUM *p, *g, *pub_key, *priv_key;
   	p = BN_new();
	g = BN_new();
	pub_key = BN_new();
	priv_key = BN_new();
	const char *c1 = "00c988d06ccd826a9351d5cae32a47b28ecc90fa4870d861ccc058cfa49419b0044a395e3f289a48c821b2efe08d293b917b1db2e2369564f5d066084f71a090706f84e101625cacaaecfff3b2fe2a8c04ff9a14d43e9b316576f1571b0fdd51a119222601ae2bbfc3007fbc12d10a2d725ad9d8503a47b4b1977faf4b0c8e244c372662a335c82380718abaa9b522a03866ebfc6dd7dee135a54fdce58eaaf1996d2485e178888f361b01c2a5f5e21e65baffe3024c02210af189975cade7bfead4a90401d7e37d9b855fa8c8f0d2fbff9357f8c05e3a2a14173e8f7555fd78b88ecedc94e238639fa1f59c896f61501b2094199d7679805fb69026d4f13cdeb60caa339beb091d7d0c125c72028fdfec35c5d6ee231b1a46c0619bf822f415121a975322001c4edc29c5caa430d1471d1013b67b90f5a7fafb322b53a9c4d418763cb8a9dd068bf3b7702ba939b4fb0da5253a999b5a8dfa664d2a9f94169f34e46d45d348e3a7e3424cf6019cfdfe1623940b3fc47a1064e601549c02020571fa10f63aeb0676213cd71d1a8a4140662d00471fe9ba88c269f8d217a978ae910a85cadca772bd7023dc8d0c2ed524c7feefedf408e4221f474a3783545e155118133fa9d65382f7261cf001701e46721021a1315780a53f4238c1aeea41d38e1b3310d2ec9ae97c2677467157a0b74da93a3cdf3e6cf898fa0f5cdf3f55ca572385698fd0f55e0e5c63b4bcb9f4a6edb74c02c0150b057b1a903f7dd8efc011ee822f2ecbb780914bcc43a11f7bf4a63be31f06226881ade9ea780a58c1a6d7183ee947611a03051a0ea817d6d26fc0c418607eef57ae00494cdda1cb518c3f910fd46c65f96e3553ceffd72d13ac13904eff4e66203b8d512bf7136251120f0bd28c1e781000bbf832a072db3bba7b2cfb5ab1f6daa17fd6ea6c484bb764e5f01194a5445b1fd435977f916261fa1b5aad6b7e83782c04ebf3cbd11dc7d929ffd8a16597e2d6a384f343d08e13cea8232818d7f989bb4b0d7d7531af0f4c6683356a109eafd135d2e3319ffa6218053ec737fbd91d5886790d4fb1db70f3d704148eff2faa0241f47f2902ea8286bd7647b615197b0e2a70f3638bdf46973518ea692da5ee26e533f815fa5e5835c2080fac1776a7ccfe2f49b1400a55f24c9fc465a766772efb35756aabf0a42b58966e883afe5e4000d863756225cdda2f5ac06093173a1afb5ad9a7b721a30820170a4ae35b3a2f09de1b53b7d7a407e0f77f1cd4201337315e6677d30ca3e40f84a7ad707be0ff99ce9334fae40692f38135dbbc8ce8e7604c0f9c8ae1989c9fe2ac29c2800dc8876032b416dd089b0f";
	const char *c2 = "05";
	int status = BN_hex2bn(&p, c1);
	std::cout<<status<<std::endl;
	status = BN_hex2bn(&g, c2);
	std::cout<<status << std::endl;
	
	DH *dh = DH_new();
	DH_set0_pqg(dh, p, NULL, g);
	status = DH_generate_key(dh);
	if(status == 0)
	{
		unsigned long err = ERR_get_error();
		char *buf = new char[512];
		ERR_error_string(err, buf);
		std::cout<<buf<<std::endl;
		delete[] buf;
	}
	//DH_get0_key(dh, const_cast<const BIGNUM**>(&pub_key), const_cast<const BIGNUM**>(&priv_key));
	int pub_size = BN_num_bytes(pub_key);
	const char *pub = new char[pub_size];
	pub = BN_bn2hex(pub_key);
	std::string e(pub);
	e = "00" + e;
	std::cout<<"e0"<<(int)(e[0])<<std::endl;
	
	std::string payload = "000003cc"
	"05"
	"20"
	"000003c1"
	+e+
	"0000000000";
	std::cout<<"payload size: " << payload.size()<<" " << e.size() <<std::endl;
	//sc.send(Host::payload_from_hex(payload));
	
	
	
	
	
	

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


	DH_free(dh);
	//BN_free(p);
	//BN_free(g);
	//BN_free(pub_key);
	//BN_free(priv_key);


	

    return 0;
}
