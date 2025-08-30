import os
import tkinter as tk
from tkinter import messagebox, ttk
from PIL import Image, ImageTk
from ProcessamentoImagem import ProcessamentoImagem

class ImagemManager:
    def __init__(self, parent, caminho):
        self.caminhoArquivo = caminho
        self.janela = parent
        self.janela.title("Processamento de imagens")
        self.janela.geometry("500x750")
        self.processamentoImagem = ProcessamentoImagem(caminho)
        self.criarWidgets()

    def criarWidgets(self):
        # Frame para a imagem
        self.imagemFrame = tk.Frame(self.janela, bg="white", relief=tk.SUNKEN, bd=2)
        self.imagemFrame.pack(pady=10, padx=10, fill=tk.BOTH, expand=True)

        self.imagemLabel = tk.Label(self.imagemFrame, text="Selecione uma imagem", 
                                bg="white", fg="gray", font=("Arial", 12))
        self.imagemLabel.pack(expand=True)
        self.carregarImagem()

        # SEÇÃO 1: ROTEAMENTO E ESPALHAMENTO
        frame_roteamento = ttk.LabelFrame(self.janela, text=" Roteamento e Espalhamento ", padding=10)
        frame_roteamento.pack(pady=10, padx=10, fill=tk.X)

        # Botões em grid - 2 por linha
        btnRotacionaDir = tk.Button(frame_roteamento, text="Rotacionar 90° a direita", 
                                command=lambda: (self.processamentoImagem.rotacao90Direita(), self.carregarImagem()))
        btnRotacionaDir.grid(row=0, column=0, padx=5, pady=5, sticky="ew")

        btnRotacionaEsq = tk.Button(frame_roteamento, text="Rotacionar 90° a esquerda", 
                                command=lambda: (self.processamentoImagem.rotacao90Esquerda(), self.carregarImagem()))
        btnRotacionaEsq.grid(row=0, column=1, padx=5, pady=5, sticky="ew")

        btnEspelhaHorizontal = tk.Button(frame_roteamento, text="Espelhar na horizontal", 
                                        command=lambda: (self.processamentoImagem.espelhamentoHorizontal(), self.carregarImagem()))
        btnEspelhaHorizontal.grid(row=1, column=0, padx=5, pady=5, sticky="ew")

        btnEspelhaVertical = tk.Button(frame_roteamento, text="Espelhar na vertical", 
                                    command=lambda: (self.processamentoImagem.espelhamentoVertical(), self.carregarImagem()))
        btnEspelhaVertical.grid(row=1, column=1, padx=5, pady=5, sticky="ew")

        # Configurar colunas com peso igual
        frame_roteamento.columnconfigure(0, weight=1)
        frame_roteamento.columnconfigure(1, weight=1)

        # SEÇÃO 2: MÁSCARA E REDUÇÃO DE RUÍDO
        frame_mascara_ruido = ttk.LabelFrame(self.janela, text=" Máscara e Redução de Ruído ", padding=10)
        frame_mascara_ruido.pack(pady=10, padx=10, fill=tk.X)

        # Tamanho da máscara - Linha 0
        self.labelTamMasc = ttk.Label(frame_mascara_ruido, text="Tamanho da máscara:")
        self.labelTamMasc.grid(row=0, column=0, padx=5, pady=5, sticky="w")

        self.comboTamMasc = ttk.Combobox(frame_mascara_ruido, values=[
            "3x3", "5x5", "7x7", "9x9", "11x11", "13x13", "15x15", "17x17", "19x19", "21x21"
        ])
        self.comboTamMasc.grid(row=0, column=1, padx=5, pady=5, sticky="ew")

        # Aplicação mascára - Linha 1
        self.labelAplMasc = ttk.Label(frame_mascara_ruido, text="Aplicação da máscara:")
        self.labelAplMasc.grid(row=1, column=0, padx=5, pady=5, sticky="w")

        self.comboAplMasc = ttk.Combobox(frame_mascara_ruido, values=["Coluna", "Linha"])
        self.comboAplMasc.grid(row=1, column=1, padx=5, pady=5, sticky="ew")

        # Redução de ruído - Linha 2
        self.labelRedRuido = ttk.Label(frame_mascara_ruido, text="Redução de ruído:")
        self.labelRedRuido.grid(row=2, column=0, padx=5, pady=5, sticky="w")

        self.comboRedRuido = ttk.Combobox(frame_mascara_ruido, values=["Mediana", "Moda"])
        self.comboRedRuido.grid(row=2, column=1, padx=5, pady=5, sticky="ew")

        # Botão aplicar máscara
        btnRotacionaDir = tk.Button(frame_mascara_ruido, text="Aplicar", 
                                command=self.aplicarMascara)
        btnRotacionaDir.grid(row=3, column=0, columnspan=2, padx=5, pady=10, sticky="ew")

        # Configurar colunas com peso igual
        frame_mascara_ruido.columnconfigure(0, weight=1)
        frame_mascara_ruido.columnconfigure(1, weight=1)

    def carregarImagem(self):
        try:
            image = self.processamentoImagem.imagemAtual

            # Redimensionar se for muito grande (mantém aspect ratio)
            max_size = (300, 300)
            image.thumbnail(max_size, Image.Resampling.LANCZOS)

            # Converter para PhotoImage (formato do Tkinter)
            self.imagem = ImageTk.PhotoImage(image)

            # Atualizar o label com a imagem
            self.imagemLabel.configure(image=self.imagem, text="")

        except Exception as e:
            messagebox.showerror("Erro", f"Não foi possível carregar a imagem:\n{str(e)}")

    def aplicarMascara(self):
        tamanhoMascara = self.comboTamMasc.get()
        aplicacaoMascara = self.comboAplMasc.get()
        reducaoRuido = self.comboRedRuido.get()

        if not tamanhoMascara or not aplicacaoMascara or not reducaoRuido:
            messagebox.showwarning("Aviso", "Preencha todos os campos!")
            return
        
        self.processamentoImagem.aplicarReducaoRuido(tamanhoMascara, aplicacaoMascara, reducaoRuido)
        self.carregarImagem()

    def run(self):
        self.janela.mainloop()
