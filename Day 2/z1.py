ulazni_rasponi_str = ""

try:
    with open('input.txt', 'r') as file:
        ulazni_rasponi_str = file.read().strip()
except FileNotFoundError:
    print("Greška: Datoteka 'input.txt' nije pronađena.")
    exit()


MAKSIMALNA_DUZINA = 10

nevažeći_id_set = set()


for duzina_pola in range(1, MAKSIMALNA_DUZINA // 2 + 1):

    minimalna_polovina = 10 ** (duzina_pola - 1)
    maksimalna_polovina = 10 ** duzina_pola

    for polovina in range(minimalna_polovina, maksimalna_polovina):
        polovina_str = str(polovina)
        nevažeći_id_str = polovina_str + polovina_str
        nevažeći_id = int(nevažeći_id_str)
        nevažeći_id_set.add(nevažeći_id)


ukupan_zbroj = 0
nevažeći_id_lista = sorted(list(nevažeći_id_set))


rasponi = ulazni_rasponi_str.split(',')

for r in rasponi:
    if '-' not in r:
        continue

    pocetak_str, kraj_str = r.split('-')

    try:
        pocetak = int(pocetak_str)
        kraj = int(kraj_str)
    except ValueError:
        continue


    for nevažeći_id in nevažeći_id_lista:
        if nevažeći_id > kraj:

            break

        if nevažeći_id >= pocetak and nevažeći_id <= kraj:
            ukupan_zbroj += nevažeći_id

print(ukupan_zbroj)