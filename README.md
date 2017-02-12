# Station-météo avec Arduino

Cette application relie un Arduino qui lit les données des capteurs * (température et humidité dans ce cas) à une application PHP qui stocke les informations sur une base de données et l'affiche avec une bibliothèque JavaScript spécifique à la visualisation des données. (D3.js)

## Pour commencer

Ces instructions vous permettront d'obtenir une copie du projet en cours d'exécution sur votre machine locale pour le développer et/ou le tester.

### Conditions préalables a avoir 

- Arduino with ehternet shield or other network interface
- Apache Web Server WAMP or LAMP
- MySQL Database Server

L'application Web peut s'exécuter dans un réseau local, à l'aide de la pile d'applications XAMP (sous linux) ou WAMP (sur Windows), mais le serveur doit être configuré pour accepter les IP locales. Ou, comme je l'ai fait, sur un serveur situé à l'extérieur de votre réseau local.

Pour savoir comment câbler l'arduino avec le capteur, s'il vous plaît se référer au guide que j'ai trouvé sur instructables [www.instructables.com/id/PART-1-Send-Arduino-data-to-the-Web-PHP-MySQL-D3js]

[www.instructables.com/id/PART-1-Send-Arduino-data-to-the-Web-PHP-MySQL-D3js]:http://www.instructables.com/id/PART-1-Send-Arduino-data-to-the-Web-PHP-MySQL-D3js/

### 1. Préparation de base de données

Tout d'abord, créez une base de données nommée quelque chose que vous aimez, puis exécutez le script sql suivant:
```sql
	CREATE TABLE tempLog (
			timeStamp TIMESTAMP NOT NULL PRIMARY KEY,
			temperature int(11) NOT NULL,
			humidity int(11) NOT NULL
	);
```
Ensuite, créez un utilisateur SQL avec privilèges de mot de passe et d'attributs pour la base de données nouvellement créée.
vous pouvez tout simplement utiliser l'utilisateur root.

Vous devrez remplacer les informations d'identification dans le fichier *** includes / connect.php *** par les nouvelles.
```php
	function Connection(){

		$server="server";
		$user="user";
		$pass="pass";
		$db="XXX";
		
		...
	}
```

### 2. Application Web PHP

Ensuite, copiez les fichiers de l'application sur un serveur, en tenant compte des éléments suivants:

- Mettez le code PHP dans la racine du serveur, et il sera accessible par:
	- **www.yourwebsite.domain**


### 3. Client Web arduino

Pour configurer le serveur auquel arduino se connecte, dans le fichier ** Arduino_client.ino **, les lignes 42 et 44 prendront l'adresse de votre propre serveur. Cette adresse peut être un domaine Web normal ou une adresse IP.

```C
	void loop(){
	
		...

		if (client.connect("www.*****.*************.com",80)) { // REMPLACER AVEC VOTRE ADRESSE SERVEUR
			... 
			client.println("Host: *****.*************.com"); // ADRESSE DE SERVEUR ICI 
			... 
		} 

		...
	}
```

Ensuite, vous pouvez charger le code sur votre Arduino et le connecter au réseau. Ce code Arduino est conçu pour utiliser les adresses IP dynamiques DHCP, de sorte qu'il peut être utilisé sur des réseaux locaux sans avoir les conflits IPs.

---

### Visualisation de données avec D3.js

Cette intégration de bibliothèque javascript rendra l'information comme dans l'image suivante.

![D3_data_viz_double_axis](https://cloud.githubusercontent.com/assets/4175297/18608876/ee4fdffe-7cec-11e6-9d6e-60c883305128.png)

L'application complète en utilisant le framework JavaScript D3.js pour afficher une impressionnante visualisation des données recueillies.


