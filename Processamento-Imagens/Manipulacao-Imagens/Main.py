from ArquivoManager import ArquivoManager
from ImagemManager import ImagemManager
import tkinter as tk
from tkinter import ttk

class Main:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Processamento de imagens")
        self.root.geometry("1100x300")
        
        self.criar_widgets()

    def criar_widgets(self):
        ArquivoManager(self.root, self)
        
        # Label para mostrar status
        self.status_label = ttk.Label(self.root, text="Nenhum arquivo selecionado")
        self.status_label.pack(pady=20)
        
        # Variável para armazenar dados entre janelas
        self.arquivoSelecionado = None

    def abrirJanelaProcessamento(self):
        # Abre a segunda janela secundária se houver arquivo selecionado
        if self.arquivoSelecionado:
            ImagemManager(self.root, self.arquivoSelecionado)
        else:
            self.status_label.config(text="Selecione um arquivo primeiro!")

    def atualizarArquivo(self, caminhoArquivo):
        # Callback chamado pela janela de seleção
        self.arquivoSelecionado = caminhoArquivo
        self.status_label.config(text=f"")
        self.abrirJanelaProcessamento()

if __name__ == "__main__":
    app = Main()
    app.root.mainloop()
