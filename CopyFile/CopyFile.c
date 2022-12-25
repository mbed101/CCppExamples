#include<cstdio>

int main()
{
	auto f = fopen("D:\\pg\\test.txt", "rb");
	fseek(f, 0, SEEK_END);
	long filelen = ftell(f);
	rewind(f);

	puts("reading\n");
	auto w = fopen("D:\\pg\\test1.txt", "wb");

	for (int i = 0; i < filelen; i++)
	{
		char c = 0;
		fread(&c, 1, 1, f);
		fwrite(&c, 1, 1, w);
	}

	auto x = fclose(f);
	auto y = fclose(w);
}
