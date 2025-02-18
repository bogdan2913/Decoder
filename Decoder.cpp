#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <map>
#include <algorithm>


using namespace std;

template<class T>
void out(T& a) {
	for (const auto& i : a) {
		cout << i.first << " " << i.second << endl;
	}
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	ifstream a("test.txt");

	map<char, unsigned> jopa;
	char ch;
	string govno;
	if (a.is_open()) {
		while (a >> ch) {
			jopa[ch]++;
			govno += ch;
		}
	}
	else { cout << "eror"; }
	a.close();

	vector<pair<char, int>> fimoz(
		jopa.begin(),
		jopa.end()
	);

	// сортируем с помощью своей лямбда-функции:
	sort(fimoz.begin(), fimoz.end(), [](const auto& p1, const auto& p2) {
		// сначала сравниваем частоты по убыванию, потом — слова по возрастанию
		return std::tie(p2.second, p1.first) < std::tie(p1.second, p2.first);
		}
	);


	char sub1 = govno[0];
	size_t i = 0;
	while (sub1 != '.' && sub1 != ',' && sub1 != '!' && sub1 != '?') {
		sub1 = govno[i];
		++i;
	}
	char probel = govno[i];

	vector<string> pipiska;
	string temp_str;

	for (char temp : govno) {
		if (temp == probel || temp == '.' || temp == ',' || temp == '!' || temp == '?' || temp == ';' || temp == ':' ||
			temp == '(' || temp == ')' || temp == '-') {
			if (!temp_str.empty()) {
				pipiska.push_back(temp_str);
				temp_str.clear();
			}
		}
		else {
			temp_str += temp;
		}
	}

	unordered_set<string> unique_words(pipiska.begin(), pipiska.end());
	vector<string> result(unique_words.begin(), unique_words.end());


	vector<pair<string, double>> zadnica;

	zadnica.emplace_back("A", 0.062);
	zadnica.emplace_back("Б", 0.014);
	zadnica.emplace_back("В", 0.038);
	zadnica.emplace_back("Г", 0.013);
	zadnica.emplace_back("Д", 0.025);
	zadnica.emplace_back("Е", 0.072);
	//zadnica.emplace_back("Ё", 0.072);
	zadnica.emplace_back("Ж", 0.077);
	zadnica.emplace_back("З", 0.016);
	zadnica.emplace_back("И", 0.062);
	zadnica.emplace_back("Й", 0.010);
	zadnica.emplace_back("К", 0.028);
	zadnica.emplace_back("Л", 0.035);
	zadnica.emplace_back("М", 0.026);
	zadnica.emplace_back("Н", 0.053);
	zadnica.emplace_back("О", 0.090);
	zadnica.emplace_back("П", 0.023);
	zadnica.emplace_back("Р", 0.040);
	zadnica.emplace_back("С", 0.045);
	zadnica.emplace_back("Т", 0.053);
	zadnica.emplace_back("У", 0.021);
	zadnica.emplace_back("Ф", 0.002);
	zadnica.emplace_back("Х", 0.009);
	zadnica.emplace_back("Ц", 0.004);
	zadnica.emplace_back("Ч", 0.012);
	zadnica.emplace_back("Ш", 0.006);
	zadnica.emplace_back("Щ", 0.003);
	zadnica.emplace_back("Ы", 0.016);
	zadnica.emplace_back("Ъ", 0.014);
	//zadnica.emplace_back("Ь", 0.014);
	zadnica.emplace_back("Э", 0.003);
	zadnica.emplace_back("Ю", 0.006);
	zadnica.emplace_back("Я", 0.018);




	sort(zadnica.begin(), zadnica.end(),
		[](const auto& p1, const auto& p2) {
		// сначала сравниваем частоты по убыванию, потом — слова по возрастанию
		return std::tie(p2.second, p1.first) < std::tie(p1.second, p2.first);
	});


	/*    double b = 0;
		for (auto i: zadnica) {
			b += i.second;
			cout << i.first << " " << i.second << endl;
	}*/



	// cout << zadnica.size() << " " << fimoz.size() - 9;

	vector<pair<string, string>> tablica; //таблица точных замен

	//////////////проверка на местоимение ее, наиболее частая биграмма
	for (auto i : result) {
		if (i.size() == 2) {
			if (i[0] == i[1]) tablica.push_back(std::pair<std::string, std::string>{std::string(1, i[0]), "Е"});
		}
	}
	/////////////


	////биграммы, которые могут быть использованы как самостоятельное слово с буквой "е" в начале:
	////т.к. е и ё - мы считаем одной буквой это одно слово - ей
	//for (auto i : result) {
	//    if (i.size() == 2) {
	//        if (i[0] == 'v' && i[1] != 'v') {
	//            tablica.push_back(std::pair<std::string, std::string>{std::string(1, i[1]), "Й"});
	//        }
	//    }
	//}
	//for (auto i : result) {
	//    if (i.size() == 2) {
	//        if (i[1] == 'v' && i[0] != i[1]) {
	//            char j = i[0];
	//            int nn = 0;
	//            for (auto m : result) {
	//                if (m.size() == 2) {
	//                    if (m[0] == j || m[1] == j) {
	//                        nn++;
	//                    }
	//                }
	//            }
	//            if (nn > 1) {
	//                //j = 'н';
	//                tablica.push_back(std::pair<std::string, std::string>{std::string(1, j), "Н"});
	//            }
	//        }
	//    }
	//}
	

	tablica.push_back(std::pair<std::string, std::string>{"j", " "});//здесь подставляются символы справа: слева - исходный символ, правильный символ
	tablica.push_back(std::pair<std::string, std::string>{"\\", "Н"});



	for (auto i : result) {
		if (i.size() == 2) {
			cout << i;
			for (const auto& j : tablica) {
				size_t pos = i.find(j.first); // Ищем символ в строке
				while (pos != string::npos) {
					i.replace(pos, 1, j.second); // Заменяем символ на строку
					pos = i.find(j.first, pos + j.second.size()); // Продолжаем поиск
				}
			}
			cout << " " << i << endl;

		}
	}

	for (auto i : result) {
		if (i.size() == 3) {
			cout << i;
			for (const auto& j : tablica) {
				size_t pos = i.find(j.first); // Ищем символ в строке
				while (pos != string::npos) {
					i.replace(pos, 1, j.second); // Заменяем символ на строку
					pos = i.find(j.first, pos + j.second.size()); // Продолжаем поиск
				}
			}
			cout << " " << i << endl;
		}
	}
	for (auto i : result) {
		if (i.size() == 4) {
			cout << i;
			for (const auto& j : tablica) {
				size_t pos = i.find(j.first); // Ищем символ в строке
				while (pos != string::npos) {
					i.replace(pos, 1, j.second); // Заменяем символ на строку
					pos = i.find(j.first, pos + j.second.size()); // Продолжаем поиск
				}
			}
			cout << " " << i << endl;
		}
	}
	for (char i : govno) {


		for (const auto& j : tablica) {
			if (i == j.first[0]) {

				i = j.second[0];
				break;
			}

		}
		cout << i;

	}

	return 0;
}
