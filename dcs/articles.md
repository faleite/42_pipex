# Summary

- Este projeto permitirá que você descubra em detalhes um mecanismo UNIX que você já conhece usando-o em seu programa.
- Este projeto é sobre o manuseio de pipes.

## 1. [Guia abrangente para Pipex](https://reactive.so/post/42-a-comprehensive-guide-to-pipex)
## 2. [Pipex Tutorial](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)

## Complemento:

### execve()

```c
#include <unistd.h>
#include <stdio.h>

int main()
{
	char *args[1];
 
	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execve("/bin/ls", &args[0], NULL);
	printf("This line will not be executed.\n");
 
	return (0);
}
```


o execve() é uma chamada de sistema que executa um programa.
o programa é passado como parâmetro para o execve() e o processo
atual é substituído pelo processo do programa que está sendo executado.
o execve() espera um array de strings com os argumentos do programa
e um array de strings com as variáveis de ambiente.
o último elemento do array de argumentos e do array de variáveis de
ambiente deve ser NULL para indicar o fim do array.
o primeiro elemento do array de argumentos é o nome do programa a ser
executado.
o primeiro elemento do array de variáveis de ambiente é o nome da
variável de ambiente e o segundo elemento é o valor da variável de
ambiente.
o execve() retorna -1 se ocorrer algum erro.

**q: explique o que acontece se o NULL for removido da linha 12**

*a: o programa não funciona, pois o execve espera um array de strings
   e o último elemento deve ser NULL para indicar o fim do array.*

q: quais sao os parametros do execve?

a: o primeiro é o nome do programa a ser executado, o segundo é um array
   de strings com os argumentos do programa e o terceiro é um array de
   strings com as variáveis de ambiente.

q: por que o printf abaixo nao eh executado?

a: o execve substitui o processo atual pelo processo do programa que
   está sendo executado, portanto, o programa atual é substituído pelo
   programa ls e o programa ls é executado. O programa atual não existe
   mais, portanto, o printf não é executado.

**q: qual a diferenca entre o execve() e o execvp()?**

- *o execve() espera um array de strings com os argumentos do programa
e um array de strings com as variáveis de ambiente.
- *o execvp() espera uma string com o nome do programa e um array de
strings com os argumentos do programa.
- *o execvp() procura o programa a ser executado no PATH do sistema.
- *o execve() não procura o programa a ser executado no PATH do sistema.*


### fork()
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main()
{
	pid_t pid;
 
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
 
	if (pid == 0)
		printf("This is the child process. (pid: %d)\n", getpid());
	else
		printf("This is the parent process. (pid: %d)\n", getpid());
 
	return (0);
}
```

O código apresentado demonstra o uso do fork(), uma chamada de sistema no Linux que cria um novo processo a partir do processo atual. Vamos analisar passo a passo:

1. Inclui as bibliotecas necessárias:
   - `<stdio.h>`: Para entrada/saída padrão.
   - `<stdlib.h>`: Para a função `exit()` e a constante `EXIT_FAILURE`.
   - `<unistd.h>`: Para a função `fork()` e a constante `pid_t`.

2. A função `main()` é definida.

3. Declaração da variável `pid` do tipo `pid_t`, que será usada para armazenar o ID do processo.

4. `pid = fork();`: A função `fork()` é chamada para criar um novo processo. O resultado da função `fork()` é atribuído à variável `pid`. O fork() cria um novo processo que é uma cópia idêntica do processo pai (exceto pelo valor de retorno do fork()).

5. `if (pid == -1) { ... }`: Verifica se ocorreu um erro ao chamar a função `fork()`. Se `fork()` retornar -1, significa que ocorreu um erro e o processo filho não foi criado. Nesse caso, uma mensagem de erro é impressa e o programa é encerrado.

6. `if (pid == 0) { ... } else { ... }`: Se `fork()` retornar 0, significa que o código está sendo executado no processo filho. O bloco de código dentro do `if` é executado, onde é impressa uma mensagem indicando que é o processo filho, juntamente com seu ID (PID) usando `getpid()`.
   - Caso contrário, se o `fork()` não retornar 0, significa que o código está sendo executado no processo pai. O bloco de código dentro do `else` é executado, onde é impressa uma mensagem indicando que é o processo pai, juntamente com seu ID (PID) usando `getpid()`.

7. `return (0);`: Termina o programa com um código de saída 0.

8. Ao passar a função `perror("fork")`, a seguinte sequência de eventos ocorre:
	1. A função `perror()` é chamada com a string `"fork"` como argumento: `perror("fork")`.
	2. A função `perror()` verifica o valor da variável global `errno` para determinar o número de erro associado.
	3. Com base no valor de `errno`, a função `perror()` imprime uma mensagem de erro correspondente na saída padrão de erro.
	4. A mensagem de erro impressa terá o seguinte formato: `"fork: mensagem_de_erro"`. A string `"fork"` é fornecida como contexto adicional para indicar o local ou a natureza da operação que resultou no erro.
	5. A mensagem de erro específica associada a `errno` é adicionada após a string `"fork:"`, fornecendo informações detalhadas sobre o erro.
	6. A mensagem de erro é impressa na saída padrão de erro, geralmente redirecionada para o terminal ou um arquivo de log, dependendo de como o programa está sendo executado. 

9. `exit(EXIT_FAILURE);`: A função `exit()` encerra o programa com um status de saída. A constante `EXIT_FAILURE` é usada como argumento para indicar que o programa está encerrando devido a uma falha ou erro. O valor de `EXIT_FAILURE` é geralmente definido como um número diferente de zero para indicar um encerramento anormal do programa.

Resumindo, o programa cria um novo processo filho a partir do processo pai usando a função `fork()`. O processo filho e o processo pai têm fluxos de execução independentes a partir do ponto em que o fork() é chamado. O processo filho é identificado pelo valor de retorno 0 do fork(), enquanto o processo pai tem um valor de retorno diferente de 0. O programa imprime uma mensagem indicando se é o processo filho ou o processo pai, juntamente com seus IDs (PIDs).




### pipe()

A função `pipe()` é uma chamada de sistema disponível em sistemas operacionais, como Unix e Linux, que permite criar um canal de comunicação unidirecional entre processos. O canal criado pelo `pipe()` é conhecido como pipe (tubo) e permite a transferência de dados de um processo para outro.

A função `pipe()` tem a seguinte assinatura:

```c
int pipe(int pipefd[2]);
```

- `pipefd`: É um array de inteiros com dois elementos. Após a chamada de `pipe()`, o array será preenchido com dois descritores de arquivo: `pipefd[0]` para leitura e `pipefd[1]` para escrita.

O funcionamento do `pipe()` é o seguinte:

1. A função `pipe()` cria um pipe vazio e retorna dois descritores de arquivo. `pipefd[0]` é usado para ler dados do pipe e `pipefd[1]` é usado para escrever dados no pipe.

2. Os processos que desejam se comunicar usando o pipe devem ter uma relação pai-filho (parent-child) ou serem processos criados por um ancestral comum que criou o pipe.

3. Um processo pode escrever dados no pipe usando o descritor de arquivo `pipefd[1]`. Esses dados serão colocados em um buffer interno do pipe.

4. Outro processo pode ler esses dados do pipe usando o descritor de arquivo `pipefd[0]`. A leitura do pipe é baseada no princípio FIFO (first-in, first-out), ou seja, os dados são lidos na ordem em que foram escritos.

5. O pipe é um mecanismo de comunicação unidirecional, o que significa que os dados fluem em uma única direção. Se houver necessidade de comunicação bidirecional, é possível criar dois pipes.

O pipe é frequentemente usado como um meio de comunicação entre processos pai e filho ou entre processos independentes. Ele permite que os processos compartilhem informações de forma simples e eficiente por meio do canal de comunicação estabelecido pelo pipe.

### envp[ ]
```c
#include <stdio.h>

// envp[] e um array de strings que contem as variaveis de ambiente
int main(int argc, char *argv[], char *envp[])
{
	for (int i=0; envp[i] != NULL; i++)
	{
		// imprime cada variavel de ambiente
		printf("%s\n", envp[i]);
	}
	return (0);
}
```