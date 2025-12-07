ukupan_napon = 0

try:
    with open('input.txt', 'r') as file:
        banke = file.readlines()
except FileNotFoundError:
    print("Greška: Datoteka 'input.txt' nije pronađena.")
    exit()

for banka_linija in banke:
    banka_linija = banka_linija.strip()

    if not banka_linija:
        continue

    maksimalni_napon_za_banku = 0
    duzina_banke = len(banka_linija)

    
    for i in range(duzina_banke):
        prva_cifra_str = banka_linija[i]


        for j in range(i + 1, duzina_banke):
            druga_cifra_str = banka_linija[j]


            napon_str = prva_cifra_str + druga_cifra_str

            try:
                trenutni_napon = int(napon_str)
            except ValueError:
                continue


            if trenutni_napon > maksimalni_napon_za_banku:
                maksimalni_napon_za_banku = trenutni_napon


    ukupan_napon += maksimalni_napon_za_banku

print(ukupan_napon)