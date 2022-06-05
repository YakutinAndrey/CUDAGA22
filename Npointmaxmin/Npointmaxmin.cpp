// A. Решение на основе принципа векторного максимина
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <chrono>

#define N 1024

int effectiveness[N][4][2];

// annual profit
int f1(int x, int z)
{
	if ((x < 1) || (x > N) || (z < 1) || (z > 4)) return 0;
	else return effectiveness[x - 1][z - 1][0];
}

// info security degree
int f2(int x, int z)
{
	if ((x < 1) || (x > N) || (z < 1) || (z > 4)) return 0;
	else return effectiveness[x - 1][z - 1][1];
}

void calcExtremePessimism(int x, int* extreme)
{
	int minf1 = f1(x, 1);
	int minf2 = f2(x, 1);
	for (int z = 2; z < 5; z++) {
		int tmp = f1(x, z);
		if (tmp < minf1) minf1 = tmp;
		tmp = f2(x, z);
		if (tmp < minf2) minf2 = tmp;
	}
	extreme[(x - 1) * 2] = minf1;
	extreme[(x - 1) * 2 + 1] = minf2;
}

struct solution {
	int x, y;
	std::string str() { return "(" + std::to_string(x) + "," + std::to_string(y) + ")"; }
	bool operator < (const solution& rhs) const {
		return (abs(x) + abs(y)) < (abs(rhs.x) + abs(rhs.y));
	}
};

inline int rand20() { return (1 + 20 * std::rand() / RAND_MAX); }

int main()
{
	std::srand(time(nullptr));
	for (int x = 0; x < N; x++) {
		for (int z = 0; z < 4; z++) {
			effectiveness[x][z][0] = rand20();
			effectiveness[x][z][1] = rand20();
		}
	}

	int extremePessimism[N][2]; // v_i = min_{z\in Z} fi(x,z)

	auto start = std::chrono::system_clock::now();
	for (int x = 1; x <= N; x++) {
		int minf1 = f1(x, 1);
		int minf2 = f2(x, 1);
		for (int z = 2; z < 5; z++) {
			int tmp = f1(x, z);
			if (tmp < minf1) minf1 = tmp;
			tmp = f2(x, z);
			if (tmp < minf2) minf2 = tmp;
		}
		extremePessimism[x - 1][0] = minf1;
		extremePessimism[x - 1][1] = minf2;
	}
	std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - start;
	std::cout << "elapsed time: " << elapsed.count() << "s\n\n";

	std::cout << "Њ­®¦Ґбвў® в®зҐЄ Єа ©­ҐЈ® ЇҐббЁ¬Ё§¬ :" << std::endl;
	for (int x = 0; x < /*N*/24; x++)
		std::cout << "(" << extremePessimism[x][0] << "," << extremePessimism[x][1] << ") ";
	std::cout << std::endl;

	std::vector<solution> effective;
	for (int x = 0; x < N; x++)
		effective.push_back(solution{ extremePessimism[x][0],extremePessimism[x][1] });
	std::sort(effective.begin(), effective.end());

	std::cout << "\nЊ­®¦Ґбвў® нддҐЄвЁў­ле аҐиҐ­Ё©:" << std::endl;
	std::cout << effective[N - 1].str() << " ";
	std::cout << effective[N - 2].str() << std::endl;

	return 0;
}
