#include "FixedLengthCoder.h"
using namespace std;

class convert {
public:
	int dec, bitlength;
	string bin; // result
};

void *enumerate(void *convert_void) {
	class convert *convert = (class convert *)convert_void;

	int bin = 0, place = 0;
	while (convert->dec > 0) { 
		bin += (convert->dec % 2) * pow(10, place);
		place++;
		convert->dec /= 2; // floor
	}

	convert->bin = string(convert->bitlength - to_string(bin).length(), '0') + to_string(bin);
	return 0;
}

int main(int argc, char *argv[]) {
	char buffer;
	string type_switch;
	letters *list = new letters;
	// ifstream ifs(argv[1]);
	ifstream ifs("input.txt"); /// for debug
	while (ifs.get(buffer)) {
		type_switch = buffer;
		if (buffer == '\n') type_switch = "<EOL>";
		list->attach(type_switch);
	}

	const int bitlength = ceil(log2(list->count));
	list->sort();

	const int THREADS = 128; // max ascii

	class convert convert[THREADS];
	pthread_t tid[THREADS];

	letter *cu = list->head;
	for (int i = 0; i < list->count; i++) {
		convert[i].dec = i;
		convert[i].bitlength = bitlength;

		if (pthread_create(&tid[i], 0, enumerate, &convert[i])) {
			std::cerr << "Thread error\n";
			return 1;
		}

		cu = cu->next;
	}

	for (int i =0; i < list->count; i++) // wait
		pthread_join(tid[i], 0);

	cu = list->head;
	for (class convert x : convert) {
		cu->code = x.bin;
		cu = cu->next;
	}

	list->restore();
	list->disp();

	return 0;
}