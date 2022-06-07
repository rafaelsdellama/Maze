## Maze

Uma matriz maze de 0s e 1s, de 10X10, representa um labirinto no qual um viajante 
precisa encontrar um caminho de maze[0][0] a maze[9][9]. O viajante pode passar de 
um quadrado para qualquer outro adjacente na mesma fileira ou coluna, mas não pode 
saltar quadrados nem se movimentar na diagonal. Além disso, o viajante não pode 
entrar num quadrado contendo um 1. maze[0][0] e maze[9][9] contêm 0s. Escreva uma 
rotina recursiva que aceite este labirinto maze e imprima uma mensagem informando a 
inexistência de um caminho através do labirinto, ou que imprima uma lista de posições 
representando um caminho de [0][0] a [9][9].