trenutna_pozicija = 50
ukupan_broj_nula = 0

with open('input.txt', 'r') as file:
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

    pocetna_pozicija = trenutna_pozicija

    if smjer == 'R':

        nova_pozicija = (pocetna_pozicija + udaljenost) % 100


        if pocetna_pozicija == 0:
            broj_nula = (udaljenost - 1) // 100
        else:
            broj_nula = (pocetna_pozicija + udaljenost) // 100

    elif smjer == 'L':

        nova_pozicija = (pocetna_pozicija - udaljenost) % 100


        if pocetna_pozicija == 0:
            broj_nula = (udaljenost - 1) // 100
        else:

            klikovi_do_nule = pocetna_pozicija
            preostali_klikovi = udaljenost - klikovi_do_nule

            if preostali_klikovi < 0:
                broj_nula = 0
            else:
                broj_nula = 1 + preostali_klikovi // 100

    ukupan_broj_nula += broj_nula
    trenutna_pozicija = nova_pozicija

print(ukupan_broj_nula)