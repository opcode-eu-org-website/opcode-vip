
// przy kompilacji konieczne jest dodanie:
//  -lsqlite3

#include <sqlite3.h>
#include <stdio.h>

/* bazę można utworzyć zarówno w poniższym kodzie poleceniami SQL,
 * jak też z poziomu powłoki:
cat << EOF | sqlite3 example.db
CREATE TABLE posts (pid INT PRIMARY KEY, uid INT, text TEXT);
INSERT INTO posts VALUES (1, 21, 'abc ..');
INSERT INTO posts VALUES (3, 2671, 'test');
EOF
*/

int main() {
	sqlite3 *db;
	if ( sqlite3_open("example.db", &db) ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	
	sqlite3_stmt *stmt;
	int ret = sqlite3_prepare_v2(db,
		"SELECT uid, text FROM posts",
		 -1, &stmt, NULL
	);
	while ( ( ret = sqlite3_step(stmt) ) == SQLITE_ROW ) {
		int uid  = sqlite3_column_int(stmt, 0);
		const char* text = (const char*) sqlite3_column_text(stmt, 1);
		printf("uid = %d, text: %s\n", uid, text);
	}
}
