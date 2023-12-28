#include <iostream>
#include <vector>
#include <random>
#include <map>
using namespace std;

class Player
{
	vector<vector<double>> money;
	vector<vector<vector<int>>> factories_conventional;
	vector<vector<vector<int>>> factories_automated;
	vector<vector<int>> ESM;
	vector<vector<int>> EGP;
	vector<vector<vector<double>>> loans;
public:
	Player(vector<vector<double>> money, vector<vector<vector<int>>> factories_conventional, vector<vector<vector<int>>> factories_automated, 
		vector<vector<int>> ESM, vector<vector<int>> EGP, vector<vector<vector<double>>> loans)
	{
		this->money = money;
		this->factories_conventional = factories_conventional;
		this->factories_automated = factories_automated;
		this->ESM = ESM;
		this->EGP = EGP;
		this->loans = loans;
	};

	double get_money(int i)
	{
		double number_money = 0;
		for (int j = 0; j < money[i].size(); j++)
			number_money += money[i][j];
		return number_money;
	}
	int get_factories_conventional(int i)
	{
		int number_factories = 0;
		for (int a = 0; a < factories_conventional[i].size(); a++)
			for (int j = 0; j < factories_conventional[i][a].size(); j++)
				if (factories_conventional[i][a][0] > 0)
				{
					number_factories += factories_conventional[i][a][0];
					break;
				}
		return number_factories;
	}
	int get_factories_automated(int i)
	{
		int number_factories = 0;
		for (int a = 0; a < factories_automated[i].size(); a++)
			for (int j = 0; j < factories_automated[i][a].size(); j++)
				if (factories_automated[i][a][0] > 0)
				{
					number_factories += factories_automated[i][a][0];
					break;
				}
		return number_factories;
	}
	void print_factories_conventional(int i)
	{
		for (int a = 0; a < factories_conventional[i].size(); a++)
		{
			for (int j = 0; j < factories_conventional[i][a].size(); j++)
			{
				if (j == 0)
					cout << "\n\tФабрик на участке №" << a + 1 << ": " << factories_conventional[i][a][0] << ";";
				else if (j == 1)
					cout << "\tКол-во месяцев до окончания строительства: " << factories_conventional[i][a][1] << "." << endl;
			}
		}
	}
	void print_factories_automated(int i)
	{
		for (int a = 0; a < factories_automated[i].size(); a++)
		{
			for (int j = 0; j < factories_automated[i][a].size(); j++)
			{
				if (j == 0)
					cout << "\n\tФабрик на участке №" << a + 1 << ": " << factories_automated[i][a][0] << ";";
				else if (j == 1)
					cout << "\tКол-во месяцев до окончания строительства / реконструкции: " << factories_automated[i][a][1] << "." << endl;
			}
		}
	}
	int get_ESM(int i)
	{
		int number_ESM = 0;
		for (int j = 0; j < ESM[i].size(); j++)
			number_ESM += ESM[i][j];
		return number_ESM;
	}
	int get_EGP(int i)
	{
		int number_EGP = 0;
		for (int j = 0; j < EGP[i].size(); j++)
			number_EGP += EGP[i][j];
		return number_EGP;
	}
	void print_loans(int i)
	{
		for (int a = 0; a < loans[i].size(); a++)
		{
			for (int j = 0; j < loans[i][a].size(); j++)
			{
				if (j == 0)
					cout << "\n\tCумма: " << loans[i][a][0] << " $;";
				else if (j == 1)
					cout << "\tКол-во месяцев до погашения: " << loans[i][a][1] << "." << endl;
			}
		}
	}

	//////////////////////////////////////////// Вывод данных игроков
	void print_players(int i)
	{
		cout << "\n\n------------------------------------------------------------------------------------------------------------------------\n\n\n"
			"Данные игрока №" << i + 1 << endl
			<< "\nСчёт: " << get_money(i)
			<< "$;\nЕдиницы сырья и материалов (ЕСМ): " << get_ESM(i)
			<< ";\nЕдиницы готовой продукции (ЕГП): " << get_EGP(i);

		cout << ";\n\nОбычные фабрики: \n"; print_factories_conventional(i);
		cout << "\n\nАвтоматизированные фабрики: \n"; print_factories_automated(i);
		cout << "\nСсуды: \n"; print_loans(i);
		cout << "\n\n------------------------------------------------------------------------------------------------------------------------\n\n";
	}
};

class Bank
{
	int level;
	int ESM_number_buy;
	int EGP_number_sell;
	int ESM_price;
	int EGP_price;
	vector<vector<int>> application;
	vector<int> consideration;
public:
	Bank(int level, int ESM_number_buy, int EGP_number_sell, int ESM_price, int EGP_price, 
		vector<vector<int>> application, vector<int> consideration)
	{
		this->level = level;
		this->ESM_number_buy = ESM_number_buy;
		this->EGP_number_sell = EGP_number_sell;
		this->ESM_price = ESM_price;
		this->EGP_price = EGP_price;
		this->application = application;
		this->consideration = consideration;
	};

	int get_level() { return level; }
	int get_ESM_buy() { return ESM_number_buy; }
	int get_EGP_sale() { return EGP_number_sell; }
	int get_max_price() { return ESM_price; }
	int get_EGP_price() { return EGP_price; }
};

//////////////////////////////////////////// Составление заявки на покупку ЕСМ (Готово)
class ApplicationESM : public Player, public Bank
{
public:

	ApplicationESM(vector<vector<double>> money, vector<vector<vector<int>>> factories_conventional, vector<vector<vector<int>>> factories_automated,
		vector<vector<int>> ESM, vector<vector<int>> EGP, vector<vector<vector<double>>> loans,
		int level, int ESM_number_buy, int EGP_number_sell, int ESM_price, int EGP_price,
		vector<vector<int>> application, vector<int> consideration) :
		Player(money, factories_conventional, factories_automated, ESM, EGP, loans),
		Bank(level, ESM_number_buy, EGP_number_sell, ESM_price, EGP_price, application, consideration)
	{}

	void acceptance_applications(int ESM_number_buy, int ESM_price, vector<vector<int>> &application, vector<int> &consideration,
		int i, int number_players)
	{
		for (int a = 0; a < number_players; a++)
			print_players(a);

		cout << "\n\n\nХод игрока №" << i + 1;

		int input_ESM;
		cout << "\n\nРаздел 'Составление заявки на покупку ЕСМ'" 
			"\n\n\n - Количество ЕСМ, выставленных на продажу в этом месяце: " << ESM_number_buy << ";"
			"\n - Их минимальная цена в этом месяце: " << ESM_price << " $."
			"\n\nВведите количество ЕСМ для покупки. \n\nПоле ввода: ";
		cin >> input_ESM;

		int input_price;
		cout << "\n\nВведите предлагаемую за них цену (Не ниже минимальной). \n\nПоле ввода : ";
		cin >> input_price;

		if (input_ESM != 0 && input_price != 0 && input_ESM <= get_ESM(i) && input_price <= get_money(i)
			&& (input_price / input_ESM) >= (ESM_price / ESM_number_buy))
		{
			application.push_back(vector<int>({ input_ESM, input_price }));
			consideration.push_back(input_price / input_ESM);

			cout << "\n\nВаша заявка была отправлена (Если на ваш адрес не был выслан товар, "
				"а со счёта не списались средства, возможно заявка другого фабриканта показалась нам более выгодной).";
		}
		else
			cout << "\nВаш запрос не был выполнен из-за недостаточного количества ресурсов / не корректно введённого запроса...";

	}
	void calculation(vector<vector<double>> &money, vector<vector<int>> &ESM, int &ESM_number_buy, 
		vector<vector<int>> &application, vector<int> &consideration)
	{
		sort(consideration.rbegin(), consideration.rend());

		if (consideration.empty())
			cout << "\n\nНи кто не подал заявок...";
		else
		{
			cout << "\n\n";
			for (int i = 0; i < consideration.size(); i++)
				for (int j = 0; j < consideration.size(); j++)
					if (ESM_number_buy >= application[j][0] && application[j][1] / application[j][0] == consideration[i])
					{
						ESM[j][0] += application[j][0];
						money[j][0] -= application[j][1];
						ESM_number_buy -= application[j][0];

						cout << "\n\t- Заявка игрока №" << j + 1 << " была принята (Количество полученных ЕСМ: " << application[j][0]
							<< "; Уплаченная сумма: " << application[j][1] << "$).";
						break;
					}
		}

		application.clear();
		consideration.clear();
	}
};

//////////////////////////////////////////// Производство ЕГП (Готово)
class ProductionEGP : public Player
{
public:
	ProductionEGP(vector<vector<double>> money, vector<vector<vector<int>>> factories_conventional, vector<vector<vector<int>>> factories_automated,
		vector<vector<int>> ESM, vector<vector<int>> EGP, vector<vector<vector<double>>> loans) :
		Player(money, factories_conventional, factories_automated, ESM, EGP, loans)
	{}

	void calculation(vector<vector<double>> &money, vector<vector<int>> &ESM, vector<vector<int>> &EGP, int i, int number_players)
	{
		for (int a = 0; a < number_players; a++)
			print_players(a);


		cout << "\n\n\nХод игрока №" << i + 1 << "\n\nРаздел 'Производство единиц готовой продукции (ЕГП)'";
		
		int choice = 0;
		while (choice != 4)
		{
			cout << "\n\n\nВыберите пункт: \n\n1. Переработать на обычной фабрике (при затратах 2000 $ на 1 ед. );"
				"\n2. Переработать на автоматизированной фабрике (при затратах 2000 $ на 1 ед. );"
				"\n3. Переработать на автоматизированной фабрике (при затратах 1500 $ на 1 ед. );"
				"\n4. Выход из раздела."
				"\n\nПоле ввода: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				int input_EGP_1;
				cout << "\n\nВведите количество ЕГП, которое желаете произвести \n\nПоле ввода: ";
				cin >> input_EGP_1;

				if (input_EGP_1 != 0 && input_EGP_1 <= get_ESM(i) && input_EGP_1 <= get_factories_conventional(i) && 
					(input_EGP_1 * 2000) <= get_money(i))
				{
					for (int j = 0; j < input_EGP_1; j++)
					{
						EGP[i][0]++;
						ESM[i][0]--;
						money[i][0] -= 2000;
					}
					cout << "\nВаш запрос был выполнен...";
				}
				else
					cout << "\nВаш запрос не был выполнен из-за недостаточного количества ресурсов / не корректно введённого запроса...";
				break;
			case 2:
				int input_EGP_2;
				cout << "\n\nВведите количество ЕГП, которое желаете произвести \n\nПоле ввода: ";
				cin >> input_EGP_2;

				if (input_EGP_2 != 0 && input_EGP_2 <= get_ESM(i) && input_EGP_2 <= get_factories_automated(i) && 
					(input_EGP_2 * 2000) <= get_money(i))
				{
					for (int j = 0; j < input_EGP_2; j++)
					{
						EGP[i][0]++;
						ESM[i][0]--;
						money[i][0] -= 2000;
					}
					cout << "\nВаш запрос был выполнен...";
				}
				else
					cout << "\nВаш запрос не был выполнен из-за недостаточного количества ресурсов / не корректно введённого запроса...";
				break;
			case 3:
				int input_EGP_3;
				cout << "\n\nВведите количество ЕГП (чётным числом), которое желаете произвести \n\nПоле ввода: ";
				cin >> input_EGP_3;

				if (input_EGP_3 != 0 && input_EGP_3 % 2 == 0 && input_EGP_3 <= get_ESM(i) &&
					input_EGP_3 <= (get_factories_automated(i) / 2) && (input_EGP_3 * 1500) <= get_money(i))
				{
					for (int j = 0; j < input_EGP_3; j++)
					{
						EGP[i][0] += 2;
						ESM[i][0] -= 2;
						money[i][0] -= 3000;
					}
					cout << "\nВаш запрос был выполнен...";
				}
				else
					cout << "\nВаш запрос не был выполнен из-за недостаточного количества ресурсов / не корректно введённого запроса...";
				break;
			default:
				break;
			}
		}
	}
};

//////////////////////////////////////////// Составление заявки на продажу ЕГП (Готово)
class SellEGP : public Player, public Bank
{
public:

	SellEGP(vector<vector<double>> money, vector<vector<vector<int>>> factories_conventional, vector<vector<vector<int>>> factories_automated,
		vector<vector<int>> ESM, vector<vector<int>> EGP, vector<vector<vector<double>>> loans,
		int level, int ESM_number_buy, int EGP_number_sell, int ESM_price, int EGP_price,
		vector<vector<int>> application, vector<int> consideration) :
		Player(money, factories_conventional, factories_automated, ESM, EGP, loans),
		Bank(level, ESM_number_buy, EGP_number_sell, ESM_price, EGP_price, application, consideration)
	{}

	void acceptance_applications(int EGP_number_sell, int EGP_price, vector<vector<int>>& application, vector<int>& consideration, 
		int i, int number_players)
	{
		for (int a = 0; a < number_players; a++)
			print_players(a);

		cout << "\n\n\nХод игрока №" << i + 1;

		int input_EGP;
		cout << "\n\nРаздел 'Составление заявки на продажу ЕГП'"
			"\n\n\n - Количество ЕГП, которые банк готов купить в этом месяце: " << EGP_number_sell << ";"
			"\n - Их максимальная цена в этом месяце: " << EGP_price << " $."
			"\n\nВведите количество ЕГП для продажи. \n\nПоле ввода: ";
		cin >> input_EGP;

		int input_price;
		cout << "\n\nВведите предлагаемую за них цену (Не выше максимальной). \n\nПоле ввода : ";
		cin >> input_price;

		if (input_EGP != 0 && input_price != 0 && input_EGP <= get_EGP(i) && input_price <= get_money(i)
			&& (input_price / input_EGP) <= (EGP_price / EGP_number_sell))
		{
			application.push_back(vector<int>({ input_EGP, input_price }));
			consideration.push_back(input_price / input_EGP);

			cout << "\n\nВаша заявка была отправлена (Если ваш счёт не был пополнен, "
				"а на складах остался товар, возможно заявка другого фабриканта показалась нам более выгодной).";
		}
		else
			cout << "\nВаш запрос не был выполнен из-за недостаточного количества ресурсов / не корректно введённого запроса...";
	}
	void calculation(vector<vector<double>>& money, vector<vector<int>>& EGP, int& EGP_number_sell,
		vector<vector<int>>& application, vector<int>& consideration)
	{
		sort(consideration.begin(), consideration.end());

		if (consideration.empty())
			cout << "\n\nНи кто не подал заявок...";
		else
		{
			cout << "\n\n";
			for (int i = 0; i < consideration.size(); i++)
				for (int j = 0; j < consideration.size(); j++)
					if (EGP_number_sell >= application[j][0] && application[j][1] / application[j][0] == consideration[i])
					{
						EGP[j][0] -= application[j][0];
						money[j][0] += application[j][1];
						EGP_number_sell -= application[j][0];

						cout << "\n\t- Заявка игрока №" << j + 1 << " была принята (Количество проданных ЕГП: " << application[j][0]
							<< "; Общая прибыль со сделки: " << application[j][1] << "$).";
						break;
					}
		}

		application.clear();
		consideration.clear();
	}
};

//////////////////////////////////////////// Выплата ссудного процента (Готово)
class LoanRepayment : public Player
{
public:
	LoanRepayment(vector<vector<double>> money, vector<vector<vector<int>>> factories_conventional, vector<vector<vector<int>>> factories_automated,
		vector<vector<int>> ESM, vector<vector<int>> EGP, vector<vector<vector<double>>> loans) :
		Player(money, factories_conventional, factories_automated, ESM, EGP, loans)
	{}

	void calculation(vector<vector<vector<double>>>& loans, vector<vector<double>>& money, int i, int number_players)
	{
		cout << "\n\n\nХод игрока №" << i + 1;

		///////////////////////// Выплата ссудного процента
		double summa_loans = 0;
		for (int a = 0; a < loans[i].size(); a++)
			for (int j = 0; j < loans[i][a].size(); j++)
				if (j == 0)
				{
					summa_loans += loans[i][a][0];
					break;
				}

		double expired_loans = 0;
		if (summa_loans != 0)
		{
			money[i][0] -= (summa_loans / 100.0);

			///////////////////////// Уменьшение срока ссуд
			for (int a = 0; a < loans[i].size(); a++)
				for (int j = 0; j < loans[i][a].size(); j++)
					if (loans[i][a][1] > 1)
					{
						cout << "1";
						loans[i][a][1]--;
						break;
					}

			///////////////////////// Погашение ссуд с истёкшим сроком
			for (int a = 0; a < loans[i].size(); a++)
				for (int j = 0; j < loans[i][a].size(); j++)
					if (loans[i][a][1] == 1)
					{
						cout << "2";

						money[i][0] -= loans[i][a][0];
						expired_loans += loans[i][a][0];

						auto iter = loans.cbegin();
						loans.erase(iter + i);

						break;
					}
		}
		cout << "\n\nРаздел 'Погашение ссуд' \n\nВ качестве выплаты ссудного процента с вашего счёта снимается сумма в размере: "
			<< summa_loans / 100 << " $; \nВы закрыли ссуды с истёкшим сроком на общую сумму в размере: " << expired_loans << " $.";
	}
};

//////////////////////////////////////////// Получение ссуды (Готово)
class LoanDisbursement : public Player
{
public:
	LoanDisbursement(vector<vector<double>> money, vector<vector<vector<int>>> factories_conventional, vector<vector<vector<int>>> factories_automated,
		vector<vector<int>> ESM, vector<vector<int>> EGP, vector<vector<vector<double>>> loans) :
		Player(money, factories_conventional, factories_automated, ESM, EGP, loans)
	{}

	void calculation(vector<vector<vector<double>>>& loans, vector<vector<double>> &money, int i, int number_players)
	{
		for (int a = 0; a < number_players; a++)
			print_players(a);

		cout << "\n\n\nХод игрока №" << i + 1;

		double summa_loans = 0;
		for (int a = 0; a < loans[i].size(); a++)
			for (int j = 0; j < loans[i][a].size(); j++)
				if (j == 0)
				{
					summa_loans += loans[i][a][0];
					break;
				}

		double loan_input;
		cout << "\n\nРаздел 'Получение ссуд' \n\nВведите сумму желаемой сcуды (В качестве отказа введите 0). \n\nПоле ввода: ";
		cin >> loan_input;

		if (loan_input != 0 && summa_loans + loan_input <= (get_factories_conventional(i) * 5000 + get_factories_automated(i) * 10000))
		{
			vector<vector<vector<double>>> loans_(number_players, vector<vector<double>>(loans[0].size() + 1, vector<double>(2, 0)));
			for (int a = 0; a < number_players; a++)
			{
				for (int j = 0; j < loans[a].size() + 1; j++)
				{
					for (int k = 0; k < 2; k++)
					{
						if (j < loans[a].size())
						{
							loans_[a][j][0] = loans[a][j][0];
							loans_[a][j][1] = loans[a][j][1];
							break;
						}
						else if (j >= loans[a].size())
						{
							loans_[a][j][0] = loan_input;
							loans_[a][j][1] = 13;
							break;
						}
					}
				}
			}
			money[i][0] += loan_input;
			loans.resize(loans_.size());
			loans[i].swap(loans_[i]);

			cout << "\n\nВаш запрос выполнен...";

			/*vector<vector<double>> loans_(loans[0].size() + 1, vector<double>(2, 0));
			for (int j = 0; j < loans[i].size() + 1; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					if (j < loans[i].size())
					{
						loans_[j][0] = loans[i][j][0];
						loans_[j][1] = loans[i][j][1];
						break;
					}
					else if (j >= loans[i].size())
					{
						loans_[j][0] = loan_input;
						loans_[j][1] = 12;
						break;
					}
				}
			}
			money[i][0] += loan_input;
			loans[i].resize(loans_.size());
			loans[i].swap(loans_);*/
		}
		else if (loan_input != 0)
			cout << "\n\nВам отказано в заявке на получение ссуды такой суммы. Так как она (учитывая остальные ссуды на вашем счету)"
				" превышает гарантированный капитал...";
	}
};

//////////////////////////////////////////// Строительство фабрик (Готово)
class FactoryConstruction : public Player
{
public:
	FactoryConstruction(vector<vector<double>> money, vector<vector<vector<int>>> factories_conventional, vector<vector<vector<int>>> factories_automated,
		vector<vector<int>> ESM, vector<vector<int>> EGP, vector<vector<vector<double>>> loans) :
		Player(money, factories_conventional, factories_automated, ESM, EGP, loans)
	{}

	void calculation(vector<vector<vector<int>>> &factories_conventional, vector<vector<vector<int>>> &factories_automated, vector<vector<double>> &money,
		int i, int number_players)
	{
		for (int a = 0; a < number_players; a++)
			print_players(a);

		cout << "\n\n\nХод игрока №" << i + 1;

		int choice = 0;
		while (choice != 4)
		{
			cout << "\n\nРаздел 'Строительство фабрик'" 
				"\n\n1. Строительство обычной фабрики (5000 долл.);" 
				"\n2. Строительство автоматизированной фабрики (10000 долл.);"
				"\n3. Реконструкция обычной фабрики в автоматизированную(7000 долл.);" 
				"\n4. Выход из раздела. \n\n\nПоле ввода : ";
			cin >> choice;

			switch (choice)
			{
			case 1:
			{
				double number_factories_1;
				cout << "\n\nКакое количество обычных фабрик вы желаете построить? \n\n\nПоле ввода: ";
				cin >> number_factories_1;

				if (get_money(i) >= (number_factories_1 * 2500))
				{
					vector<vector<vector<int>>> factories_conventional_(number_players, vector<vector<int>>
						(factories_conventional[0].size() + number_factories_1, vector<int>(2, 0)));
					for (int a = 0; a < number_players; a++)
					{
						for (int j = 0; j < factories_conventional[a].size() + number_factories_1; j++)
						{
							for (int k = 0; k < 2; k++)
							{
								if (j < factories_conventional[a].size())
								{
									factories_conventional_[a][j][0] = factories_conventional[a][j][0];
									factories_conventional_[a][j][1] = factories_conventional[a][j][1];
									break;
								}
								else if (j >= factories_conventional[a].size())
								{
									factories_conventional_[a][j][0] = 0;
									factories_conventional_[a][j][1] = 6;
									money[i][0] -= 2500;
									break;
								}
							}
						}
					}
					factories_conventional.resize(factories_conventional_.size());
					factories_conventional[i].swap(factories_conventional_[i]);

					cout << "\n\nВаш запрос выполнен...";
				}
				else
					cout << "\n\nНа вашем счёте недостаточно средств...";
				break;
			}
			case 2:
			{
				int number_factories_2;
				cout << "\n\nКакое количество автоматизированных фабрик вы желаете построить? \n\n\nПоле ввода: ";
				cin >> number_factories_2;

				if (get_money(i) >= (number_factories_2 * 5000))
				{
					vector<vector<vector<int>>> factories_automated_(number_players, vector<vector<int>>
						(factories_automated[0].size() + number_factories_2, vector<int>(3, 0)));
					for (int a = 0; a < number_players; a++)
					{
						for (int j = 0; j < factories_automated[a].size() + number_factories_2; j++)
						{
							for (int k = 0; k < 3; k++)
							{
								if (j < factories_automated[a].size())
								{
									factories_automated_[a][j][0] = factories_automated[a][j][0];
									factories_automated_[a][j][1] = factories_automated[a][j][1];
									factories_automated_[a][j][2] = factories_automated[a][j][2];
									break;
								}
								else if (j >= factories_automated[a].size())
								{
									factories_automated_[a][j][0] = 0;
									factories_automated_[a][j][1] = 8;
									factories_automated_[a][j][2] = -2;
									money[i][0] -= 5000;
									break;
								}
							}
						}
					}
					factories_automated.resize(factories_automated_.size());
					factories_automated[i].swap(factories_automated_[i]);

					cout << "\n\nВаш запрос выполнен...";
				}
				else
					cout << "\n\nНа вашем счёте недостаточно средств...";
				break;
			}
			case 3:
			{
				int number_factories_3 = 0;
				for (int a = 0; a < factories_conventional[i].size(); a++)
					for (int j = 0; j < factories_conventional[i][a].size(); j++)
						if (factories_conventional[i][a][0] > 0)
						{
							number_factories_3 += factories_conventional[i][a][0];
							break;
						}

				int number_reconstruction;
				cout << "\n\nКакое количество фабрик вы желаете реконструировать? \n\n\nПоле ввода: ";
				cin >> number_reconstruction;

				if (number_factories_3 != 0 && number_factories_3 >= number_reconstruction && get_money(i) >= (number_reconstruction * 7000))
				{
					vector<vector<vector<int>>> factories_automated_rec(number_players, vector<vector<int>>
						(factories_automated[0].size() + number_reconstruction, vector<int>(3, 0)));
					for (int a = 0; a < number_players; a++)
					{
						for (int j = 0; j < factories_automated[a].size() + number_reconstruction; j++)
						{
							for (int k = 0; k < 3; k++)
							{
								if (j < factories_automated[a].size())
								{
									factories_automated_rec[a][j][0] = factories_automated[a][j][0];
									factories_automated_rec[a][j][1] = factories_automated[a][j][1];
									factories_automated_rec[a][j][2] = factories_automated[a][j][2];
									break;
								}
								else if (j >= factories_automated[a].size())
								{
									factories_automated_rec[a][j][0] = 0;
									factories_automated_rec[a][j][1] = 9;
									factories_automated_rec[a][j][2] = -1;
									money[i][0] -= 7000;
									break;
								}
							}
						}
					}
					factories_automated.resize(factories_automated_rec.size());
					factories_automated[i].swap(factories_automated_rec[i]);

					cout << "\n\nВаш запрос выполнен...";
				}
				else
					cout << "\n\nВаших финансов и/или имущества недостаточно для реконструкции такого масштаба...";
				break;
			}
			default:
				break;
			}
		}

		for (int a = 0; a < factories_conventional[i].size(); a++)             //Уменьшение оставшегося срока строительства 'обычных' фабрик
			for (int j = 0; j < factories_conventional[i][a].size(); j++)
			{
				if (factories_conventional[i][a][1] == 1)
				{
					factories_conventional[i][a][0] = 1;
					factories_conventional[i][a][1] = 0;
					money[i][0] -= 2500;
					break;
				}
				else if (factories_conventional[i][a][1] > 1)
				{
					factories_conventional[i][a][1]--;
					break;
				}
			}

		for (int a = 0; a < factories_automated[i].size(); a++)                //Уменьшение оставшегося срока строительства 'автоматизированных' фабрик
			for (int j = 0; j < factories_automated[i][a].size(); j++)
			{
				if (factories_automated[i][a][1] == 1)
				{
					factories_automated[i][a][0] = 1;
					factories_automated[i][a][1] = 0;
					money[i][0] -= 5000;
					break;
				}
				else if (factories_automated[i][a][1] > 1)
				{
					factories_automated[i][a][1]--;
					break;
				}
			}

		for (int a = 0; a < factories_automated[i].size(); a++)                //Уменьшение оставшегося срока реконструкции 'обычных' фабрик
			for (int j = 0; j < factories_automated[i][a].size(); j++)
				if (factories_automated[i][a][0] == 1 && factories_automated[i][a][2] == -1)
				{
					auto iter = factories_conventional.cbegin();
					factories_conventional.erase(iter + 0);
					factories_automated[i][a][2] = -2;
					break;
				}
	}
};

//////////////////////////////////////////// Выплата постоянных издержек (Готово)
class PaymentСosts : public Player
{
public:
	PaymentСosts(vector<vector<double>> money, vector<vector<vector<int>>> factories_conventional, vector<vector<vector<int>>> factories_automated,
		vector<vector<int>> ESM, vector<vector<int>> EGP, vector<vector<vector<double>>> loans) :
		Player(money, factories_conventional, factories_automated, ESM, EGP, loans)
	{}

	void calculation(vector<vector<double>> &money, vector<vector<vector<int>>> &factories_conventional, vector<vector<vector<int>>>&factories_automated,
		vector<vector<int>> &ESM, vector<vector<int>> &EGP, vector<vector<vector<double>>> &loans, int i, int &number_players)
	{
		for (int a = 0; a < number_players; a++)
			print_players(a);

		cout << "\n\n\nХод игрока №" << i + 1;

		cout << "\n\nРаздел 'Выплата постоянных издержек' с вашего счёта списывается сумма за владение..."
			<< "\n\n... обычными фабриками в размере: " << get_factories_conventional(i) * 1000
			<< "$; \n... автоматизированными фабриками в размере: " << get_factories_automated(i) * 1500
			<< "$; \n... единицами сырья и материалов (ЕСМ) в размере: " << get_ESM(i) * 300
			<< "$; \n... единицами готовой продукции (ЕГП) в размере: " << get_EGP(i) * 500 << " $."
			<< "\n\nИтог: " << ((get_factories_conventional(i) * 1000) + (get_factories_automated(i) * 1500) + (get_ESM(i) * 300) + (get_EGP(i) * 500))
			<< " $.";
		cout << "\n\nБлагодарим за понимание!" << endl;

		money[i][0] -= ((get_factories_conventional(i) * 1000) + (get_factories_automated(i) * 1500) + (get_ESM(i) * 300) + (get_EGP(i) * 500));

		//////////////////////////////////////////// Удаление обанкротившихся игроков
		if (money[i][0] <= 0)
		{
			cout << "\nИгрок №" << i + 1 << " обанкротился!! Его порядковый номер переходит другому игроку.";

			auto iter_1 = money.cbegin();
			money.erase(iter_1 + i);

			auto iter_2 = factories_conventional.cbegin();
			factories_conventional.erase(iter_2 + i);

			auto iter_3 = factories_automated.cbegin();
			factories_automated.erase(iter_3 + i);

			auto iter_4 = ESM.cbegin();
			ESM.erase(iter_4 + i);

			auto iter_5 = EGP.cbegin();
			EGP.erase(iter_5 + i);

			auto iter_6 = loans.cbegin();
			loans.erase(iter_6 + i);

			number_players--;
		}
	}
};

//////////////////////////////////////////// Определение обстановки на рынке (Готово)
class MarketEnvironment : public Bank
{
public:
	MarketEnvironment(int level, int ESM_number_buy, int EGP_number_sell, int ESM_price, int EGP_price,
		vector<vector<int>> application, vector<int> consideration) :
		Bank(level, ESM_number_buy, EGP_number_sell, ESM_price, EGP_price, application, consideration)
	{}

	void calculation(int number_players, int &level, int &ESM_number_buy, int &EGP_number_sell, int &ESM_price, int &EGP_price)
	{
		random_device rd;
		mt19937 gen(rd());

		discrete_distribution<> distr({});

		if (get_level() == 1)
			distr = { 0, 0.33, 0.33, 0.16, 0.083, 0.083 };
		else if (get_level() == 2)
			distr = { 0, 0.25, 0.33, 0.25, 0.083, 0.083 };
		else if (get_level() == 3)
			distr = { 0, 0.083, 0.25, 0.33, 0.25, 0.083 };
		else if (get_level() == 4)
			distr = { 0, 0.083, 0.083, 0.25, 0.33, 0.25 };
		else if (get_level() == 5)
			distr = { 0, 0.083, 0.083, 0.16, 0.33, 0.33 };

		map<int, int> histogram;
		for (int i = 0; i < 1; ++i)
			++histogram[distr(gen)];

		for (const auto& elem : histogram)
			level = elem.first;

		if (level == 1)
		{
			ESM_number_buy = round(1.0 * number_players);
			EGP_number_sell = round(3.0 * number_players);
			ESM_price = 800;
			EGP_price = 6500;
		}
		else if (level == 2)
		{
			ESM_number_buy = round(1.5 * number_players);
			EGP_number_sell = round(2.5 * number_players);
			ESM_price = 650;
			EGP_price = 6000;
		}
		else if (level == 3)
		{
			ESM_number_buy = round(2.0 * number_players);
			EGP_number_sell = round(2.0 * number_players);
			ESM_price = 500;
			EGP_price = 5500;
		}
		else if (level == 4)
		{
			ESM_number_buy = round(2.5 * number_players);
			EGP_number_sell = round(1.5 * number_players);
			ESM_price = 400;
			EGP_price = 5000;
		}
		else if (level == 5)
		{
			ESM_number_buy = round(3.0 * number_players);
			EGP_number_sell = round(1.0 * number_players);
			ESM_price = 300;
			EGP_price = 4500;
		}
	}
};

int main()
{
	system("chcp 1251");

	int number_players;
	cout << "\n\nВведите количество игроков. \n\nПоле ввода: ";
	cin >> number_players;

	int end_game;
	cout << "\n\nВведите количество игровых месяцев. \n\nПоле ввода: ";
	cin >> end_game;


	//В начале у игроков: 10000 $, 2 обычные фабрики, 0 автоматизированных, 4 ЕСМ,
	// 2 ЕГП, 0 ссудов и звание старшего, которое даётся первому по счёту
	vector<vector<double>> money;
	for (int i = 0; i < number_players; i++)
		money.push_back(vector<double>({ 10000 }));

	vector<vector<vector<int>>> factories_conventional(number_players, vector<vector<int>>(2, vector<int>(2, 0)));
	for (int i = 0; i < number_players; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
			{
				if (k == 0)
					factories_conventional[i][j][k] = 1;
				else if (k == 1)
					factories_conventional[i][j][k] = 0;
			}

	vector<vector<int>> ESM;
	for (int i = 0; i < number_players; i++)
		ESM.push_back(vector<int>({ 4 }));

	vector<vector<int>> EGP;
	for (int i = 0; i < number_players; i++)
		EGP.push_back(vector<int>({ 2 }));

	vector<vector<vector<int>>> factories_automated(number_players, vector<vector<int>>(2, vector<int>(2)));
	vector<vector<vector<double>>> loans(number_players, vector<vector<double>>(2, vector<double>(2)));


	//В начале банк имеет: 3 уровень, количество ESM = 2.0 * number_players, минимальную цену на ЕСМ в размере 500$,
	// количество EGP = 2.0 * number_players, максимальную цену на ЕГП в размере 5500$
	int level = 3;
	int ESM_number_buy = round(2.0 * number_players);
	int EGP_number_sell = round(2.0 * number_players);
	int ESM_price = 500;
	int EGP_price = 5500;
	vector<vector<int>> application;
	vector<int> consideration;

	while (end_game != 0 || number_players != 1 || number_players != 0)
	{
		//////////////////////////////////////////// Покупка ЕСМ
		for (int i = 0; i < number_players; i++)
		{
			ApplicationESM application_ESM(money, factories_conventional, factories_automated, ESM, EGP, loans,
				level, ESM_number_buy, EGP_number_sell, ESM_price, EGP_price, application, consideration);
			application_ESM.acceptance_applications(ESM_number_buy, ESM_price, application, consideration, i, number_players);
		}
		ApplicationESM application_ESM(money, factories_conventional, factories_automated, ESM, EGP, loans,
			level, ESM_number_buy, EGP_number_sell, ESM_price, EGP_price, application, consideration);
		application_ESM.calculation(money, ESM, ESM_number_buy, application, consideration);

		//////////////////////////////////////////// Производство ЕГП
		for (int i = 0; i < number_players; i++)
		{
			ProductionEGP production_EGP(money, factories_conventional, factories_automated, ESM, EGP, loans);
			production_EGP.calculation(money, ESM, EGP, i, number_players);
		}

		//////////////////////////////////////////// Продажа ЕГП
		for (int i = 0; i < number_players; i++)
		{
			SellEGP sell_EGP(money, factories_conventional, factories_automated, ESM, EGP, loans,
				level, ESM_number_buy, EGP_number_sell, ESM_price, EGP_price, application, consideration);
			sell_EGP.acceptance_applications(EGP_number_sell, EGP_price, application, consideration, i, number_players);
		}
		SellEGP sell_EGP(money, factories_conventional, factories_automated, ESM, EGP, loans,
			level, ESM_number_buy, EGP_number_sell, ESM_price, EGP_price, application, consideration);
		sell_EGP.calculation(money, EGP, EGP_number_sell, application, consideration);

		//////////////////////////////////////////// Выплата ссудного процента
		for (int i = 0; i < number_players; i++)
		{
			LoanRepayment loan_repayment(money, factories_conventional, factories_automated, ESM, EGP, loans);
			loan_repayment.calculation(loans, money, i, number_players);
		}

		//////////////////////////////////////////// Получение ссуды
		for (int i = 0; i < number_players; i++)
		{
			LoanDisbursement loan_disbursement(money, factories_conventional, factories_automated, ESM, EGP, loans);
			loan_disbursement.calculation(loans, money, i, number_players);
		}

		//////////////////////////////////////////// Строительство фабрик
		for (int i = 0; i < number_players; i++)
		{
			FactoryConstruction factory_construction(money, factories_conventional, factories_automated, ESM, EGP, loans);
			factory_construction.calculation(factories_conventional, factories_automated, money, i, number_players);
		}

		//////////////////////////////////////////// Выплата постоянных издержек
		for (int i = 0; i < number_players; i++)
		{
			PaymentСosts payment_costs(money, factories_conventional, factories_automated, ESM, EGP, loans);
			payment_costs.calculation(money, factories_conventional, factories_automated, ESM, EGP, loans, i, number_players);
		}

		//////////////////////////////////////////// Определение обстановки на рынке
		MarketEnvironment market_environment(level, ESM_number_buy, EGP_number_sell, ESM_price, EGP_price, application, consideration);
		market_environment.calculation(number_players, level, ESM_number_buy, EGP_number_sell, ESM_price, EGP_price);

		//////////////////////////////////////////// Уменьшение количества оставшихся месяцев (ходов)
		end_game--;
	}


	Player player(money, factories_conventional, factories_automated, ESM, EGP, loans);
	vector<int> winner;
	for (int i = 0; i < number_players; i++)
		winner.push_back((player.get_factories_conventional(i) * 5000) + (player.get_factories_automated(i) * 10000) +
			(player.get_ESM(i) + ESM_price) + (player.get_EGP(i) + EGP_price) + (player.get_money(i)));

	sort(winner.rbegin(), winner.rend());

	cout << "\n\n";
	for (int i = 0; i < winner.size(); i++)
		for (int j = 0; j < winner.size(); j++)
		{
			if (i == 0 && ((player.get_factories_conventional(i) * 5000) + (player.get_factories_automated(i) * 10000) +
				(player.get_ESM(i) + ESM_price) + (player.get_EGP(i) + EGP_price) + (player.get_money(i))) == winner[i])
			{
				cout << "\n\n'Распределение игроков по общему капиталу'\n\n" << i + 1 << " место: Игрок №" << j + 1 <<
					" с общим капиталом в размере: " << winner[i] << " $" << endl;
				break;
			}
			else if (i != 0 && ((player.get_factories_conventional(i) * 5000) + (player.get_factories_automated(i) * 10000) +
				(player.get_ESM(i) + ESM_price) + (player.get_EGP(i) + EGP_price) + (player.get_money(i))) == winner[i])
			{
				cout << i + 1 << " место: Игрок №" << j + 1 <<
					" с общим капиталом в размере: " << winner[i] << " $" << endl;
				break;
			}
		}
}