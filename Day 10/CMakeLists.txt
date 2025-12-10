# Minimalna potrebna verzija CMake
# Preporučuje se novija verzija, npr. 3.10 ili 3.16
cmake_minimum_required(VERSION 3.10)

# Ime projekta
# Ovo se koristi za postavljanje varijabli i opće reference
project(AdventOfCodeDay9 CXX)

# Postavljanje standarda za C++ (npr. C++17)
# Važno za moderni C++ kod
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Definiranje izvršne datoteke (exe)
# Prvi argument je ime koje će se koristiti za generiranje izvršne datoteke (npr. "z2")
# Drugi argumenti su SVE vaše .cpp datoteke koje sadrže kod
add_executable(z2
        z2.cpp
        input_reader.cpp
)

# Napomena: Ako je vaša datoteka input_reader.cpp u istom direktoriju kao z2.cpp,
# onda je putanja samo "input_reader.cpp". Ako je u poddirektoriju "utils",
# onda je putanja "utils/input_reader.cpp". Prilagodite ovo.

# Preporučena opcija: Uključivanje putanja za headere (nije striktno potrebno ako su svi u projektu)
# Uklanja potrebu za apsolutnim putanjama u #include naredbama
# target_include_directories(z2 PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/utils
# )