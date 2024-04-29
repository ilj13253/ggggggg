#include <iostream>
#include <Windows.h>
#include <fstream>
#include<List>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;
class Student {
private:
	int score = 0; string name = "", subject = "";
public:
	int GetScore()const {
		return score;
	}
	Student(string name, string subject) :name(name), subject(subject) {}
	void SetScore(int Score) {
		this->score = Score;
	}
	string GetName()const {
		return name;
	}
	string GetSub()const {
		return subject;
	}
	friend ostream& operator<<(ostream& os, const Student s)
	{
		os << "Имя:" << s.name << "Предмет" << s.subject << "Оценки:" << s.score << endl;
		return os;
	}
	bool operator<(const Student& ss)const
	{
		return score < ss.score;
	}
};
class StudentFile :Student {
private:
	list<Student>group;
public:
	StudentFile(const string& name, const string& subject) : Student(name, subject) {}
	void setpush(const Student& s) {
		group.push_back(s);
	}
	void updScore(const string& name, int newScore) {
		for (auto& i : group)
		{
			if (i.GetName() == name)
			{
				i.SetScore(newScore);
				break;
			}
		}
	}
	void RemoveStudent(const string& name) {
		group.remove_if([name](const Student& student) {
			return student.GetName() == name;
			});
	}

	void SortByScore(bool ascending = true) {
		group.sort();
		if (!ascending) {
			group.reverse();
		}
	}

	void PrintStudents() const {
		for (const auto& student : group) {
			cout << student << endl;
		}
	}

	void WriteToFile(const string& filename) const {
		ofstream file(filename);
		if (file.is_open()) {
			for (const auto& student : group) {
				file << student.GetName() << " " << student.GetSub() << " " << student.GetScore() << endl;
			}
			file.close();
		}
		else {
			cout << "Не удается открыть файл: " << filename << endl;
		}
	}

	void ReadFromFile(const string& filename) {
		group.clear();
		ifstream file(filename);
		if (file.is_open()) {
			string name, subject;
			int score;
			while (file >> name >> subject >> score) {
				group.push_back(Student(name, subject));
				group.back().SetScore(score);
			}
			file.close();
		}
		else {
			cout << "Не удается открыть файл " << filename << endl;
		}

	}
};
class pop {
private:
public:
	bool isSymmetric(const string& word) {
		int len = word.length();
		for (int i = 0; i < len / 2; ++i) {
			if (word[i] != word[len - i - 1]) {
				return false;
			}
		}
		return true;
	}

	void printSymmetricWords(const string& filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Не удается открыть файл:" << filename << endl;
			return;
		}

		vector<string> words;
		string word;
		while (file >> word) {
			words.push_back(word);
		}
		file.close();

		// Print symmetric words excluding the last one
		for (size_t i = 0; i < words.size() - 1; ++i) {
			if (isSymmetric(words[i])) {
				cout << words[i] << endl;
			}
		}
	}
	void removeDuplicates(const string& inputFilename, const string& outputFilename) {
		ifstream inputFile(inputFilename);
		if (!inputFile.is_open()) {
			cout << "Не удается открыть входной файл: " << inputFilename << endl;
			return;
		}

		unordered_set<string> uniqueWords;
		string word;
		while (inputFile >> word) {
			uniqueWords.insert(word);
		}
		inputFile.close();

		ofstream outputFile(outputFilename);
		if (!outputFile.is_open()) {
			cout << "Не удается открыть выходной файл:" << outputFilename << endl;
			return;
		}

		for (const auto& word : uniqueWords) {
			outputFile << word << endl;
		}
		outputFile.close();

		cout << "Удаленные дубликаты и записанные в " << outputFilename << endl;
	}
};
int main()
{
	setlocale(LC_ALL, "rus"); SetConsoleCP(1251);
	StudentFile manager("default name", "default subject");;
	manager.ReadFromFile("students.txt");
	manager.updScore("Илья", 95);

	// Удаление студента
	manager.RemoveStudent("Алиса");

	// Сортировка студентов по оценке
	manager.SortByScore();

	// Вывод списка студентов
	manager.PrintStudents();

	// Запись данных в файл
	manager.WriteToFile("sorted_students.txt");

	pop i;
	string filename;
	cout << "Введите имя файла: ";
	cin >> filename;
	i.printSymmetricWords(filename);


	string inputFilename, outputFilename;
	cout << "Введите имя входного файла: ";
	cin >> inputFilename;
	cout << "Введите имя выходного файла: ";
	cin >> outputFilename;
	i.removeDuplicates(inputFilename, outputFilename);
}