from flask import Flask, request, jsonify, render_template, flash, redirect, url_for
import psycopg2
from config import Config
from forms import LoginForm, RegistrationForm
from flask_bootstrap import Bootstrap
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import create_engine, MetaData, Table, Column, Integer, String
from flask_login import LoginManager, UserMixin, current_user, login_user, login_required, logout_user
from sqlalchemy.orm import sessionmaker
import datetime


path="postgresql://davide:12345@localhost/physa"
engine = create_engine(path, echo=True)
meta = MetaData()

conn = engine.connect()
cursor = ''

def get_current_date():
	now = datetime.datetime.now()
	#-------------------------
	#-------------------------
	day = str(now.day)
	if len(day) < 2:
		day = '0' + day
	#-------------------------
	#-------------------------
	month = str(now.month)
	if len(month) < 2:
		month = '0' + month
	#-------------------------
	#-------------------------
	hour = str(now.hour - 1)
	if hour == '-1':
		hour = '23'
	if len(hour) < 2:
		hour = '0' + hour
	#-------------------------
	#-------------------------
	minute = str(now.minute)
	if len(minute) < 2:
		minute = '0' + minute
	return day +"."+ month + " " + hour + ":" + minute


def connect():
	global cursor
	conn = psycopg2.connect(
		host="localhost",
		database="physa",
		user="davide",
		password="12345")

	cursor = conn.cursor()
	'''
	cursor.execute('SELECT * FROM test')
	records = cursor.fetchall()
	for i in records:
		print("ID = ", i[0], " name = ", i[1])
		'''
	return 1

connect()
app = Flask(__name__)
bootstrap = Bootstrap(app)
login = LoginManager(app)
db = SQLAlchemy(app)
app.config.from_object(Config)
dicta ={
	"3":"50w",
	"1234":75
}

@login.user_loader
def load_user(aid):
	return session.query(user_model).filter_by(id = aid).first()

class user_name(db.Model):
	"""docstring for user_name"""
	email = db.Column(db.String, primary_key = True)
	name = db.Column(db.String)
		

class user_model(db.Model, UserMixin):
	"""docstring for user_model"""
	__tablename__ = 'user_model'
	id = db.Column(db.Integer, primary_key=True)
	password = db.Column(db.String)
	name = db.Column(db.String)
		
class train_data(db.Model):
	"""docstring for train_data"""
	__tablename__ = "trainer data"
	name = db.Column(db.String, primary_key=True)
	card_id = db.Column(db.String)
	total = db.Column(db.Integer)
	last_time = db.Column(db.String)
	itera = db.Column(db.Integer)


'''user_model = Table(
	'user_model', meta,
	Column('id', Integer, primary_key = True),
	Column('password', String),
	Column('name', String),

)'''


Session = sessionmaker(bind = engine)
session = Session()
@app.route('/user/', methods=['GET', 'POST'])
def user_alt():# рут для получения чека
	cursor.execute('SELECT train FROM test')
	records = cursor.fetchall()[0]

	return render_template("about.html", data = records[0])


@app.route('/check/', methods=['GET', 'POST'])
def getcheck_alt():# рут для получения чека
	data = request.get_json()
	data["id"] = data["id"][0:-1]
	print (data)
	user = session.query(train_data).filter_by(card_id = data["id"]).first()
	user.total += user.itera
	user.last_time = get_current_date() 
	session.commit()
	print(user.itera)
	
	return "15"#"Вам осталось 3 приседания 3"

@app.route('/getTrain/', methods=['GET', 'POST'])
def gettrain():# рут для получения чека
	data = request.get_json()
	data["id"] = data["id"][0:-1]
	user = session.query(train_data).filter_by(card_id = data["id"]).first()
	return str(user.itera)

#J6LKXDH5 MGTS_GPON_7B08




@app.route('/enter/', methods=['GET', 'POST'])
def enter_login():# рут для получения чека	
	if current_user.is_authenticated:
		return redirect(url_for('index'))
	if request.method == "POST":
		username = request.form.get("email")
		password = request.form.get("password")
		user = session.query(user_model).filter_by(name = username).first()
		if user.password == password:
			login_user(user)
			flash(' All correct')
			return redirect('/user/' + username)
		flash("incorrect username or password.")
		
    #user = find_user(username)

    #if user and password == user.password:
    #    return redirect("profile")
    #else:

	return render_template("login.html")

@login_required
@app.route('/user/<username>', methods=['GET', 'POST'])
def user(username):# рут для получения чека
	user = session.query(user_model).filter_by(name = current_user.name).first()
	data = session.query(user_name).filter_by(email = current_user.name).first()
	user_alt = session.query(train_data).filter_by(name = current_user.name).first()
	flash(current_user.name)
	return render_template("profile.html", name = data.name, time = user_alt.last_time, count = user_alt.total, iter = user_alt.itera)

@app.route('/index')
def index():
	return render_template('inde.html')

@app.route('/logout')
def logout():
	logout_user()
	return redirect(url_for('index'))

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)# отключить debug


