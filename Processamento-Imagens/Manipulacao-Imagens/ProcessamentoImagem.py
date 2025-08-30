from PIL import Image
import numpy as np

class ProcessamentoImagem:
    def __init__(self, caminho):
        self.caminhoImagem = caminho
        self.importarImagem()

    def importarImagem(self):
        # Importa imagem e converte para tons de cinza
        self.imagemOriginal = Image.open(self.caminhoImagem).convert('L')
        self.matrizOriginal = np.array(self.imagemOriginal)
        self.imagemAtual = self.imagemOriginal
        self.matrizAtual = self.matrizOriginal
        self.altura = 0
        self.largura = 0

        # Salva a imagem original em txt
        self.salvaMatrizTxt("matrizPixels_original.txt")
        
        self.recriarImagem()

    def salvaMatrizTxt(self, nomeArquivo):
        self.converteMatrizToTxt(self.matrizAtual, nomeArquivo)

    # Converte a matriz para um arquivo txt
    def converteMatrizToTxt(self, matriz, nomeArquivo):
        self.altura, self.largura = matriz.shape
        linhas_txt = [f"Imagem tamanho {self.altura}x{self.largura}\n"]

        for linha in range(self.altura):
            textoLinha = ""
            for coluna in range(self.largura):
                pixel = matriz[linha][coluna]
                textoLinha += str(pixel).rjust(3)
                if coluna != (self.largura - 1):
                    textoLinha += ", "

            textoLinha += "\n"
            linhas_txt.append(textoLinha)

        with open(nomeArquivo, "w", encoding="utf-8") as arquivo:
            for linha in linhas_txt:
                arquivo.write(linha)

    def recriarImagem(self):
        self.imagemAtual = Image.fromarray(self.matrizAtual, mode='L')
        self.imagemAtual.save("imagem_atual.jpg")
    
    # Rotação 90° para a direita (horário)
    def rotacao90Direita(self):
        self.matrizAtual = np.rot90(self.matrizAtual, k=3)
        self.salvaMatrizTxt("matrizPixels_atual.txt")
        self.recriarImagem()

    # Rotação 90° para a esquerda (anti-horário)
    def rotacao90Esquerda(self):
        self.matrizAtual = np.rot90(self.matrizAtual, k=1)
        self.salvaMatrizTxt("matrizPixels_atual.txt")
        self.recriarImagem()

    def espelhamentoVertical(self): 
        self.matrizAtual = np.fliplr(self.matrizAtual)
        self.salvaMatrizTxt("matrizPixels_atual.txt")
        self.recriarImagem()

    def espelhamentoHorizontal(self):
        self.matrizAtual = np.flipud(self.matrizAtual)
        self.salvaMatrizTxt("matrizPixels_atual.txt")
        self.recriarImagem()

    def aplicarReducaoRuido(self, tamanhoMasc, aplicacaoMascara, reducaoRuido):
        posicaoX = tamanhoMasc.find("x")
        if posicaoX != -1:
            self.tamanhoMascara = int(tamanhoMasc[:posicaoX])
        
        self.matrizAtual = self.aplicarMascara(self.tamanhoMascara, aplicacaoMascara, reducaoRuido)
        
        self.salvaMatrizTxt("matrizPixels_atual.txt")
        self.recriarImagem()
    
    def aplicarMascara(self, tamMascara, aplicacaoMascara, reducaoRuido):
        matrizAtualizada = self.matrizAtual
        linInicio, colInicio = 0, 0
        posicaoCentral = tamMascara // 2

        linFinal = linInicio + tamMascara
        colFinal = colInicio + tamMascara

        while linFinal < self.altura and colFinal < self.largura:        
            #print("Linha: " + str(linInicio) + " " + str(linFinal))    
            #print("Colun: " + str(colInicio) + " " + str(colFinal))  
            subMatriz = self.matrizAtual[linInicio:linFinal, colInicio:colFinal]
            media = self.calcularMedias(subMatriz, reducaoRuido)

            matrizAtualizada[linInicio+posicaoCentral][colInicio+posicaoCentral] = media

            if aplicacaoMascara == "Linha":
                linInicio += 1
                if linInicio + tamMascara >= self.altura and colFinal < self.largura:
                    linInicio = 0
                    colInicio += 1

            elif aplicacaoMascara == "Coluna":
                colInicio += 1
                if colInicio + tamMascara >= self.largura and linFinal < self.altura:
                    colInicio = 0
                    linInicio += 1
            
            linFinal = linInicio + tamMascara
            colFinal = colInicio + tamMascara

        return matrizAtualizada

    def calcularMedias(self, subMatriz, reducaoRuido):
        valoresPixels = []
        for linha in subMatriz:
            #print(linha)
            for coluna in linha:
                valoresPixels.append(int(coluna))
        
        if reducaoRuido == "Mediana":
            media = np.median(valoresPixels)
            media = int(media)
            #print ("Media: " + str(media))
        elif reducaoRuido == "Moda":
            media = self.calcularModa(valoresPixels)
            #print ("Media: " + str(media))

        return media

    def calcularModa(self, array):
        # Passo 1: Obter valores únicos e suas contagens
        valoresUnicos, contagens = np.unique(array, return_counts=True)
    
        # Passo 2: Encontrar o índice do valor com maior contagem
        indiceModa = np.argmax(contagens)
    
        # Passo 3: Retornar o valor da moda e sua contagem
        moda = valoresUnicos[indiceModa]
    
        return moda
