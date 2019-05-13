
import sqlite3
import os.path

if os.path.isfile('example.db'):
	create = False
else:
	create = True
conn = sqlite3.connect('example.db')
c = conn.cursor()

if create:
	print("create new db")
	c.execute("CREATE TABLE users (uid INT PRIMARY KEY, name TEXT);")
	c.execute("CREATE TABLE posts (pid INT PRIMARY KEY, uid INT, text TEXT);")
	
	c.execute("INSERT INTO users VALUES (21, 'user A');")
	c.execute("INSERT INTO users VALUES (2671, 'user B');")
	
	c.execute("INSERT INTO posts VALUES (1, 21, 'abc ..');")
	c.execute("INSERT INTO posts VALUES (2, 21, 'qwe xyz');")
	c.execute("INSERT INTO posts VALUES (3, 2671, 'test');")

	conn.commit()

maxUid = 100
for r in c.execute("SELECT * FROM users WHERE uid < ?;", (maxUid,)):
	print(r)

for r in c.execute("""SELECT u.name, p.text FROM
                      users AS u JOIN posts AS p ON (u.uid = p.uid);"""):
	print(r)
