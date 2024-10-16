import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv('resultados.csv', header=None, names=['N', 'compares'])


error = data['compares'].std() / (len(data) ** 0.5)


plt.figure(figsize=(12, 8))


plt.errorbar(data['N'], data['compares'], yerr=error, fmt='o', 
             color='red', ecolor='black', capsize=5, label='Promedio de Comparaciones', markersize=8)


plt.plot(data['N'], data['compares'], color='blue', alpha=0.5, linewidth=2)


plt.title('Número de Operaciones por Cantidad de Datos', fontsize=20)
plt.xlabel('Número de Claves N', fontsize=16)
plt.ylabel('Comparaciones', fontsize=16)


plt.yscale('log')


plt.xlim(100, 10000)
plt.ylim(1e-07, 1e-05) 


plt.xticks(fontsize=14)
plt.yticks(fontsize=14)
plt.grid(True, linestyle='--', alpha=0.7)


plt.legend(fontsize=14)


plt.savefig('grafico.png', dpi=300) 
plt.show()
