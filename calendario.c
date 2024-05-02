#include <stdio.h>

/*Esta função verifica se um ano é bissexto ou não.
Se um ano é bissexto, significa que fevereiro terá 29 dias em vez de 28.
Para saber se um ano é bissexto, ela usa uma regra simples: se o ano for divisível por 4, ele pode ser bissexto. Mas existem exceções. Por exemplo, anos como 1900 não são bissextos, mesmo sendo divisíveis por 4, porque também são divisíveis por 100. No entanto, anos como 2000 são bissextos porque são divisíveis por 400.
A função retorna 1 se o ano for bissexto e 0 se não for.*/

int ehBissexto(int ano) {
return (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
}

 /*Esta função nos ajuda a descobrir quantos dias tem um mês específico.
A quantidade de dias em um mês depende do mês em questão e, em alguns casos, do ano também (devido ao ano bissexto).
Por exemplo, fevereiro tem 28 dias na maioria dos anos, mas em anos bissextos tem 29 dias.
O objetivo dessa função é retornar o número correto de dias para o mês e ano especificados.*/

int diasNoMes(int mes, int ano) {
 if (mes == 2) // Fevereiro
     return (ehBissexto(ano) ? 29 : 28);
  else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) // Abril, Junho, Setembro, Novembro
        return 30;
  else // Outros meses
        return 31;
}

  /*Esta função é responsável por mostrar o calendário de um mês específico na tela.
Para fazer isso, precisamos saber qual é o primeiro dia da semana em que o mês começa.
Com essa informação, podemos imprimir os números dos dias do mês, organizando-os em uma tabela que represente um calendário.Use um switch para poder colocar os meses dentro de cada case e um for, para percorrer um loop, de dias da semana.*/

void imprimirCalendario(int mes, int ano, int primeiroDia) {
    int i, j, dia = 1;
    printf("\n*** CALENDÁRIO ***\n");
    switch (mes) {
        case 1: printf("Janeiro\n"); break;
        case 2: printf("Fevereiro\n"); break;
        case 3: printf("Março\n"); break;
        case 4: printf("Abril\n"); break;
        case 5: printf("Maio\n"); break;
        case 6: printf("Junho\n"); break;
        case 7: printf("Julho\n"); break;
        case 8: printf("Agosto\n"); break;
        case 9: printf("Setembro\n"); break;
        case 10: printf("Outubro\n"); break;
        case 11: printf("Novembro\n"); break;
        case 12: printf("Dezembro\n"); break;
    }
    printf("Dom Seg Ter Qua Qui Sex Sab\n");
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 7; j++) {
            if ((i == 0 && j < primeiroDia) || dia > diasNoMes(mes, ano))
                printf("    ");
            else
                printf("%3d ", dia++);
        }
        printf("\n");
    }
}

  /*função main(), é tipo o centro das atenções. Primeiro, ela pede pro usuário algumas informações, tipo o ano e em que dia da semana começa o ano. Depois, mostra um menu com umas opções: ver o calendário do ano, marcar eventos ou ver o calendário com os eventos marcados. Se o usuário escolher ver o calendário do ano, ele chama uma função chamada imprimirCalendario(). Se ele quiser marcar um evento, aí chama a função agendarEvento(). Essa função main() tá sempre controlando tudo, garantindo que o que o usuário quer seja feito direitinho.*/


int main() {
    int ano, primeiroDia, opcao, mes, dia, duracao; // declaração de variaveis
    int agendamentos[12][31] = {0}; // Inicializa todos os dias com 0 agendamentos

    printf("Digite o ano: ");
    scanf("%d", &ano);

    printf("Digite o dia da semana em que 1º de janeiro cai (0 - Domingo, 1 - Segunda, ..., 6 - Sábado): ");
    scanf("%d", &primeiroDia);

   /*O loop do-while é utilizado para garantir que o menu de opções seja exibido pelo menos uma vez e continuar mostrando o menu até que o usuário escolha a opção de sair (opção 0).*/

    do {
      printf("\nMenu:\n");
      printf("(1) Mostrar calendário\n");
      printf("(2) Inserir agendamento\n");
      printf("(3) Mostrar calendário com agendamentos\n");
      printf("(0) Sair\n");
      printf("Escolha uma opção: ");
      scanf("%d", &opcao);

   /*A estrutura switch-case é usada para direcionar o programa com base na escolha do usuário no menu de opções. Dependendo da opção selecionada (opcao), diferentes partes do código são executadas, porem O loop for percorre os meses do ano (de 1 a 12) porque o usuário quer ver o calendário de todos os meses. Isso significa que o programa imprimirá o calendário de cada mês um por um, na ordem, para que o usuário possa ver todos os meses sequencialmente*/

        switch (opcao) {
            case 1:
                for (mes = 1; mes <= 12; mes++) {
                    imprimirCalendario(mes, ano, primeiroDia);
                    printf("\n");
                }
                break;
          
          /* Quando o usuário seleciona a opção case 2, o programa solicita o mês e o dia de início do agendamento, bem como a duração em dias. Em seguida, ele verifica se há conflitos de agendamento para cada dia no período selecionado e o loop for é utilizado para verificar cada dia no período de agendamento e verificar se há conflitos de agendamento.  */
            
            case 2:
                printf("Digite o mês e o dia de início do agendamento (formato: Mês Dia): ");
                scanf("%d %d", &mes, &dia);
                printf("Digite a duração do agendamento em dias: ");
                scanf("%d", &duracao);

                int i;
                for (i = 0; i < duracao; i++) {
                    if (agendamentos[mes - 1][dia - 1 + i] >= 5) {
                        printf("Não é possível agendar nesse dia devido a conflito de agendamentos.\n");
                        break;
                    }
                }
        /*if é utilizado para verificar se tem erros de agendamento para cada dia no período selecionado. Ele é essencial para garantir que o programa possa informar imediatamente ao usuário caso algum dia selecionado já esteja ocupado. Se um conflito for detectado, o programa exibe uma mensagem informando que não é possível agendar nesse dia devido ao conflito de agendamentos.*/

                if (i == duracao) {
                 for (i = 0; i < duracao; i++) {
                    agendamentos[mes - 1][dia - 1 + i]++;
                    }
                 printf("Agendamento realizado com sucesso!\n");
                }
                break;

       /* opção 3, que é "Mostrar calendário com agendamentos", há outro loop for que itera sobre os meses do ano (de 0 a 11). Este loop também é necessário para percorrer cada mês e imprimir o calendário com os agendamentos associados a cada dia.*/        
            case 3:
                printf("\n*** CALENDÁRIO DE AGENDAMENTOS ***\n");
                for (mes = 0; mes < 12; mes++) {
                    imprimirCalendario(mes + 1, ano, primeiroDia);
                    printf("\n");
                    printf("Dom Seg Ter Qua Qui Sex Sab\n");
                    for (int dia = 0; dia < diasNoMes(mes + 1, ano); dia++) {
                        printf("%3d ", agendamentos[mes][dia]);
                    }
                    printf("\n");
                }
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
   
   /*while. Este loop garante que o menu de opções seja exibido continuamente até que o usuário escolha sair do programa  clicando na (opção 0). Depois que o bloco switch é executado, o programa verifica se a condição opcao != 0 é verdadeira. Se for, o loop while continua executando e o menu de opções é exibido novamente para que o usuário possa fazer outra escolha. Se o usuário selecionar a opção 0 para sair, o loop do-while é encerrado e o programa termina.*/

    return 0;
}
