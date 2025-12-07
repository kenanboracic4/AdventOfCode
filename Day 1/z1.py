trenutna_pozicija = 50
broj_nula = 0

with open('Input.txt', 'r') as file:
    rotacije = file.readlines()

for rotacija_linija in rotacije:
    rotacija_linija = rotacija_linija.strip()

    if not rotacija_linija:
        continue

    smjer = rotacija_linija[0]
    udaljenost_str = rotacija_linija[1:]


    try:
        udaljenost = int(udaljenost_str)
    except ValueError:
        continue

    if smjer == 'R':

        trenutna_pozicija = (trenutna_pozicija + udaljenost) % 100
    elif smjer == 'L':

        trenutna_pozicija = (trenutna_pozicija - udaljenost) % 100


    if trenutna_pozicija == 0:
        broj_nula += 1

print(broj_nula)