extern void main_host_test();
extern void main_frames_test();
extern void main_encryption_test();
extern void main_frame_packer_test();
#include <iostream>

int main()
{
	main_host_test();
	main_frames_test();
	main_encryption_test();
	main_frame_packer_test();
	return 0;
}

