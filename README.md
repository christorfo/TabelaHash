# Gerenciador de Contatos com Tabela Hash em C

Este projeto é uma aplicação em linguagem C para gerenciar contatos utilizando uma tabela hash como estrutura de dados. Ele foi desenvolvido com o objetivo de explorar conceitos de estruturas de dados, funções hash e manipulação de memória dinâmica.

##  Funcionalidades

- **Adicionar Contato**  
  Permite registrar um contato com nome e número de telefone no formato `41 98888 8899`. O número é formatado automaticamente para exibição no formato `(41) 98888-8899`.

- **Buscar Contato**  
  Pesquisa contatos pelo nome, exibindo o número correspondente e o tempo de busca.

- **Remover Contato**  
  Remove um contato da tabela hash, se existente.

- **Exibir Todos os Contatos**  
  Lista todos os contatos armazenados, organizados pelos índices da tabela hash.

##  Tecnologias e Técnicas Utilizadas

- **Linguagem:** C
- **Estruturas de Dados:**  
  - Tabela hash com encadeamento para lidar com colisões.  
  - Função hash baseada no algoritmo djb2.
- **Manipulação de Strings:**  
  - Validação de números de telefone.  
  - Formatação automática para exibição.  

##  Como Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/christorfo/gerenciador-contatos-hash.git
   cd gerenciador-contatos-hash
##  Observações

- O programa valida o formato de números de telefone no padrão brasileiro, exigindo 11 dígitos numéricos (incluindo o DDD).
- O tamanho da tabela hash pode ser ajustado na constante TABLE_SIZE, permitindo testar o impacto das colisões na performance.
- Durante a exibição dos contatos, os números são automaticamente formatados para (DDD) 99999-9999.

##  Aprendizados e Aplicações
Este projeto foi desenvolvido para consolidar os seguintes conceitos:

- Implementação de tabelas hash em C.
- Resolução de colisões usando encadeamento.
- Manipulação de memória dinâmica com malloc e free.
- Formatação e validação de entradas do usuário.
