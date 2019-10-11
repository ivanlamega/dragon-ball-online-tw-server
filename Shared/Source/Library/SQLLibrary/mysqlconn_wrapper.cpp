#include <mysqlconn_wrapper.h>
#include <Logger.h>

using namespace std;
MySQLConnWrapper::~MySQLConnWrapper()
{
	if (con != NULL)
	{
		con->close();
		delete con;
	}
}
MySQLConnWrapper::MySQLConnWrapper()
{
	host = "tcp://127.0.0.1:3306";
	user = "root";
	password = "ascent";
	con = NULL;
};
void MySQLConnWrapper::manageException(sql::SQLException& e)
{
	if (e.getErrorCode() != 0) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}
void MySQLConnWrapper::Ping()
{
	sql::ResultSet* result = executes("SELECT 1;");
	if (result != NULL)
		delete result;
}
/*
	username , password , host , db
*/
void MySQLConnWrapper::setInfos(string _username, string _password, string _host, string _dbmmoDB)
{
	user = _username;
	if (_password != "" && _password != " " && _password.length() >= 2)
		password = _password;
	else
		password = "";
	host = _host;
	dbmmoDB = _dbmmoDB;
}
bool MySQLConnWrapper::connect()
{
	try
	{
		driver = get_driver_instance();
	}
	catch (sql::SQLException &e)
	{
		manageException(e);
		return false;
	}
	try
	{
		con = driver->connect(host, user, password);
	}
	catch (sql::SQLException &e)
	{
		manageException(e);
		return false;
	}
	return true;
}
bool MySQLConnWrapper::switchDb(const string& db_name)
{
	try
	{
		con->setSchema(db_name);
	}
	catch (sql::SQLException &e)
	{
		manageException(e);
		return false;
	}
	return true;
}
sql::ResultSet* MySQLConnWrapper::executes(const char* format, ...)
{
	m_mutex.lock();

	if (!format)
	{
		m_mutex.unlock();
		return NULL;
	}
	va_list ap;
	char szQuery[MAX_QUERY_LEN];
	va_start(ap, format);
	int res = vsnprintf(szQuery, MAX_QUERY_LEN, format, ap);
	va_end(ap);
	if (res == -1)
	{
		sLog.outError("SQL Query truncated (and not execute) for format: %s", format);
		m_mutex.unlock();
		return NULL;
	}
	try
	{
		sLog.outDebug("Requested query:\n%s", szQuery);
		sql::Statement *statement = con->createStatement();
		sql::ResultSet* result = statement->executeQuery(szQuery);
		delete statement;
		if (result != NULL)
			result->next();
		m_mutex.unlock();
		return result;
	}
	catch (sql::SQLException &e)
	{
		manageException(e);
	}

	m_mutex.unlock();

	return NULL;
}
