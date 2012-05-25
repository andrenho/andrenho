#include "city/City.h"
#include "ui/UI.h"

int main(int argc, char* argv[])
{
	City* city = new City();
	UI* ui = new UI(city);

	while(ui->Active())
	{
		ui->Draw();
		ui->Input();
		city->Process();
		ui->Wait();
	}

	return 0;
}
