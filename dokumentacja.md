# 1. Utwórz katalog lab
mkdir ~/lab

# 2. Wyświetl prawa dostępu do katalogu lab
ls -ld ~/lab

# 3. Nadaj uprawnienia: odczyt i wejście dla grupy, usuń dla innych
chmod 750 ~/lab

# 4. Zapisz szczegółową zawartość katalogu /boot do pliku lab/boot.txt
ls -l /boot > ~/lab/boot.txt

# 5. Utwórz strukturę katalogów dir1/dir2/dir3 w katalogu lab
mkdir -p ~/lab/dir1/dir2/dir3

# 6. Będąc w katalogu lab/dir1/dir2/ wyświetl zawartość pliku lab/boot.txt (ścieżka relatywna)
cd ~/lab/dir1/dir2
cat ../../boot.txt

# 7. Utwórz puste pliki tekst1.txt, tekst2.txt, tekst3.txt w katalogu lab
touch ~/lab/tekst1.txt ~/lab/tekst2.txt ~/lab/tekst3.txt

# 8. Skopiuj pliki tekst1.txt, tekst2.txt, tekst3.txt do katalogu lab/dir1/dir2/dir3/
cp ~/lab/tekst*.txt ~/lab/dir1/dir2/dir3/

# 9. Utwórz ukryty plik o dowolnej nazwie w katalogu lab
touch ~/lab/.ukryty

# 10. Zmień nazwę dowolnego pliku w katalogu lab/dir1/dir2/dir3
mv ~/lab/dir1/dir2/dir3/tekst1.txt ~/lab/dir1/dir2/dir3/zmieniony.txt

# 11. Zapisz zawartość /proc/meminfo do pliku lab/tekst1.txt
cat /proc/meminfo > ~/lab/tekst1.txt

# 12. Dodaj zawartość /proc/cpuinfo do pliku lab/tekst1.txt
cat /proc/cpuinfo >> ~/lab/tekst1.txt

# 13. Zapisz kto jest zalogowany obecnie w systemie do pliku lab/tekst2.txt
who > ~/lab/tekst2.txt

# 14. Znajdź wszystkie katalogi o nazwie share w /
find / -type d -name share 2>/dev/null

# 15. Znajdź wszystkie pliki > 5 MB w /usr/bin
find /usr/bin -type f -size +5M 2>/dev/null

# 16. Skopiuj wszystkie pliki zwykłe o rozmiarze 300–500 bajtów z /usr/bin do lab
find /usr/bin -type f -size +300c -size -500c -exec cp {} ~/lab/ \; 2>/dev/null

# 17. Utwórz dowiązanie twarde do pliku lab/tekst2.txt
ln ~/lab/tekst2.txt ~/lab/TEKST2.TXT

# 18. Utwórz dowiązanie symboliczne do pliku lab/tekst2.txt
ln -s ~/lab/tekst2.txt ~/lab/Tekst2.txt

# 19. Wyświetl wszystkie elementy z katalogu lab (łącznie z ukrytymi)
ls -la ~/lab

# 20. Wyświetl pliki zawierające 'tty' w nazwie z katalogu /dev
ls /dev | grep tty

# 21. Z man dowiedz się, jak wyświetlić zawartość folderu lab wraz z podfolderami
# (Opcja -R)
ls -R ~/lab

