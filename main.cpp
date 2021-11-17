#include <dirent.h>
#include <fstream>
#include <iostream>

using namespace std;

void encryptFile(string fileName) {
  fstream sourceFile, tempFile;
  string tempFileName = "temp.txt";
  char byte;

  sourceFile.open(fileName, ios::in);
  tempFile.open(tempFileName, ios::out | ios::trunc);

  while (sourceFile >> noskipws >> byte) {
    byte += 1;
    tempFile << byte;
  }

  sourceFile.close();
  tempFile.close();

  sourceFile.open(fileName, ios::out | ios::trunc);
  tempFile.open(tempFileName, ios::in);

  while (tempFile >> noskipws >> byte) {
    sourceFile << byte;
  }

  sourceFile.close();
  tempFile.close();
  remove(tempFileName.c_str());
}

void decryptFile(string fileName) {
  fstream sourceFile, tempFile;
  string tempFileName = "temp.txt";
  char byte;

  sourceFile.open(fileName, ios::in);
  tempFile.open(tempFileName, ios::out | ios::trunc);

  while (sourceFile >> noskipws >> byte) {
    byte -= 1;
    tempFile << byte;
  }

  sourceFile.close();
  tempFile.close();

  sourceFile.open(fileName, ios::out | ios::trunc);
  tempFile.open(tempFileName, ios::in);

  while (tempFile >> noskipws >> byte) {
    sourceFile << byte;
  }

  sourceFile.close();
  tempFile.close();
  remove(tempFileName.c_str());
}

void encryptDirectory(string directoryName) {
  DIR *directory;
  struct dirent *directoryItem;
  string fileName;
  string currentDirectory = directoryName + "/.";
  string parentDirectory = directoryName + "/..";

  if ((directory = opendir(directoryName.c_str())) != NULL) {
    while ((directoryItem = readdir(directory)) != NULL) {
      fileName = directoryName + "/" + directoryItem->d_name;
      if ((fileName != currentDirectory) && (fileName != parentDirectory)) {
        encryptFile(fileName);
        cout << fileName << " encriptado!!" << endl;
      }
    }
  }
}

void decryptDirectory(string directoryName) {
  DIR *directory;
  struct dirent *directoryItem;
  string fileName;
  string currentDirectory = directoryName + "/.";
  string parentDirectory = directoryName + "/..";

  if ((directory = opendir(directoryName.c_str())) != NULL) {
    while ((directoryItem = readdir(directory)) != NULL) {
      fileName = directoryName + "/" + directoryItem->d_name;
      if ((fileName != currentDirectory) && (fileName != parentDirectory)) {
        decryptFile(fileName);
        cout << fileName << " decriptado!" << endl;
      }
    }
  }
}

int main() {
  string directoryName;

  cout << "Insira o diretório a ser encriptado: ";
  cin >> directoryName;
  fflush(stdin);
  encryptDirectory(directoryName);

  cout << "Insira o diretório a ser decriptado: ";
  cin >> directoryName;
  fflush(stdin);
  decryptDirectory(directoryName);

  cin.get();

  return 0;
}
