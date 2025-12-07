ulazni_rasponi_str = ""

try:
    with open('input.txt', 'r') as file:
        ulazni_rasponi_str = file.read().strip()
except FileNotFoundError:
    print("Greška: Datoteka 'input.txt' nije pronađena.")
    exit()

MAKSIMALNA_DUZINA = 10
nevažeći_id_set = set()


for duzina_subniza in range(1, MAKSIMALNA_DUZINA // 2 + 1):


    maks_ponavljanja = MAKSIMALNA_DUZINA // duzina_subniza


    minimalni_A = 10 ** (duzina_subniza - 1)
    maksimalni_A = 10 ** duzina_subniza

    for subniz in range(minimalni_A, maksimalni_A):
        subniz_str = str(subniz)


        for n in range(2, maks_ponavljanja + 1):
            nevažeći_id_str = subniz_str * n


            if len(nevažeći_id_str) > MAKSIMALNA_DUZINA:
                continue

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