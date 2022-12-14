#include <iostream>
#include <string>
#include "circuito.h"

//Erika Fernanda da Silva Oliveira (20190084385)
//Felipe Gabriel B. da Silva (20200069600)

using namespace std;

void gerarTabela(Circuito& C);

int main(void)
{
  Circuito C;
  string nome;
  int opcao;

  do {
    cout << "\nPROGRAMA SIMULADOR DE CIRCUITOS DIGITAIS:\n";
    do {
      cout << "0 - Sair\n";
      cout << "1 - Digitar um circuito via teclado\n";
      cout << "2 - Salvar um circuito em arquivo\n";
      cout << "3 - Ler um circuito de arquivo\n";
      cout << "4 - Imprimir o circuito na tela\n";
      cout << "5 - Simular o circuito para todas as entrada (gerar tabela verdade)\n";
      cout << "Qual sua opcao? ";
      cin >> opcao;
    } while(opcao<0 || opcao>5);
    switch(opcao){
    case 1:
      C.digitar();
      break;
    case 2:
      cout << "Caminho: ";
      getline(cin,nome);
      C.salvar(nome);
    case 3:
      // Antes de ler a string com o nome do arquivo, esvaziar o buffer do teclado
      cin.ignore(256,'\n');
      
      do {
        cout << "Arquivo: ";
        getline(cin,nome);
      } while (nome.size() < 3); // Name do arquivo >= 3 caracteres
      if (opcao==3) {
        if (!C.ler(nome))
        {
          // Erro na leitura
          cerr << "Arquivo " << nome << " invalido para leitura\n";
        }
      }
      else {
        if (!C.salvar(nome))
        {
          // Erro no salvamento
          cerr << "Arquivo " << nome << " invalido para escrita\n";
        }
      }
      break;
    case 4:
      C.imprimir();
      break;
    case 5:
      gerarTabela(C);
      break;
    default:
      break;
    }
  } while(opcao != 0);
}

void gerarTabela(Circuito& C)
{
  vector<bool3S> in_circ(C.getNumInputs());
  int i;
  for (i=0; i<C.getNumInputs(); i++)
  {
    in_circ.at(i) = bool3S::UNDEF;
  }

  cout << "ENTRADAS" << '\t' << "SAIDAS" << endl;
  do
  {
    C.simular(in_circ);
    for (i=0; i<C.getNumInputs(); i++)
    {
      cout << in_circ.at(i);
      if (i<C.getNumInputs()-1) cout << ' ';
      else
      {
        cout <<'\t';
        if (C.getNumInputs()<=2) cout <<'\t';
      }
    }
    for (i=0; i<C.getNumOutputs(); i++)
    {
      cout << C.getOutput(i+1);
      if (i<C.getNumOutputs()-1) cout << ' ';
      else cout << '\n';
    }
i = C.getNumInputs()-1;
    while (i>=0 && in_circ.at(i)==bool3S::TRUE)
    {
      in_circ.at(i)++;
      i--;
    };
    if (i>=0) in_circ.at(i)++;
  } while (i>=0);
}

