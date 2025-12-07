def pronadji_najveci_podniz(banka_linija, ciljana_duzina):



    N = len(banka_linija)
   
    K = N - ciljana_duzina


    if N < ciljana_duzina:
        return 0

    rezultat = []

    for cifra in banka_linija:


        while K > 0 and rezultat and cifra > rezultat[-1]:
            rezultat.pop()
            K -= 1

        rezultat.append(cifra)


    if K > 0:
        rezultat = rezultat[:-K]


    return "".join(rezultat)


ukupan_zbroj_str = 0

try:
    with open('input.txt', 'r') as file:
        banke = file.readlines()
except FileNotFoundError:
    print("Greška: Datoteka 'input.txt' nije pronađena.")
    exit()

prvi_put = True
for banka_linija in banke:
    banka_linija = banka_linija.strip()

    if not banka_linija or len(banka_linija) < 12:
        continue

    najveci_napon_str = pronadji_najveci_podniz(banka_linija, 12)

    if najveci_napon_str:

        trenutni_napon = int(najveci_napon_str)

        if prvi_put:
            ukupan_zbroj_str = trenutni_napon
            prvi_put = False
        else:
            ukupan_zbroj_str += trenutni_napon

print(ukupan_zbroj_str)