def prebroji_pristupacne_rolne(mreza):

    broj_redova = len(mreza)
    if broj_redova == 0:
        return 0

    broj_kolona = len(mreza[0])
    pristupacne_rolne = 0


    smjerovi = [
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1), (0, 1),
        (1, -1), (1, 0), (1, 1)
    ]


    for r in range(broj_redova):
        for k in range(broj_kolona):


            if mreza[r][k] == '@':

                susjedne_rolne = 0


                for dr, dk in smjerovi:
                    susjed_r, susjed_k = r + dr, k + dk


                    if 0 <= susjed_r < broj_redova and 0 <= susjed_k < broj_kolona:


                        if mreza[susjed_r][susjed_k] == '@':
                            susjedne_rolne += 1


                if susjedne_rolne < 4:
                    pristupacne_rolne += 1

    return pristupacne_rolne



try:
    with open('input.txt', 'r') as file:
        ulazna_mreza = [linija.strip() for linija in file.readlines() if linija.strip()]
except FileNotFoundError:
    print("Greška: Datoteka 'input.txt' nije pronađena.")
    exit()

rezultat = prebroji_pristupacne_rolne(ulazna_mreza)
print(rezultat)