//Arquivo de cabeçalho da funções

//Estrutura de Dados representando um ponto
typedef struct {
	float coordX; 
	float coordY;
} tPonto;

//Funções para os casos de teste
float funcA(float x);

float funcB(float x);

float funcC(float x);

float funcD(float x);

float funcE(float x);

float funcF(float x);

float funcG(float x);

//Funcao para calcular a área dos retângulos
float area(tPonto ini, tPonto fim);

//Função sequencial da integracao numérica
float integracao_numerica(float a, float b, float erro, char funcao);
