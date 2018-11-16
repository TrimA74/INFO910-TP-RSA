# TP3 RSA
Ce TP a pour but de réaliser des programmes permettant de chiffrer, déchiffrer, signer et vérifier la signature.
Ce TP utilise la librairie GMP en C++, qui permet de gérer les grands entiers.

## Comment installer GMP
1. Rendez-vous sur le site [GMP](https://gmplib.org/) et téléchargez l'archive.
2. Extraire l'archive où vous voulez !
3. Ouvrez ensuite un terminal et saisissez la commande :
*     sudo ./configure
*     sudo make
*     sudo make check
*     sudo make install
Par défaut, gmp est installé dans /usr/local.

## Avancement du TP

Toutes les questions ont été abordés.

## Liste des exécutables
- `./gencle` Programme pour générer une pair de clés RSA
- `./chiffre` Programme pour chiffre un texte sur l'entrée standard avec la clé public passé en paramètre
- `./dechiffre` Programme pour déchiffrer un message chiffré sur l'entrée standard avec la clé privée passé en paramètre
- `./signe` Programme pour signer le hacher d'un message sur l'entrée standard avec la clé privée passé en paramètre
- `./verifie` Programme pour vérifier la signature d'un message
- `./inverse-modulaire` Programme qui compare l'inverse modulaire que nous avons implémenté avec mpz_invert

## How to use RSA

Alice veut envoyer un message à Bob :

- Example : `./gencle 32 bob` ( génération de la pair de clés pour Bob )
- Example : `./gencle 32 alice` ( génération de la pair de clés pour Alice )
- Example : `cat message.txt | ./chiffre bob` ( chiffrement du message par Alice avec la clé publique de Bob)
- Example : `cat message.chiffre | ./dechiffre bob` ( Bob déchiffre le message chiffré d'Alice avec sa propre clé privée )
- Example : `cat message.txt | ./signe alice` ( Alice signe son message avec sa clé privée )
- Example : `cat message.txt | ./verifie alice message`  ( Bob véréfie que c'est bien Alice qui a envoyé le message avec la clé public d'Alice )
