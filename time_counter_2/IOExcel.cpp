#include "IOExcel.h"



void IOExcel::Start_Excel()
{
	//Initialise COM interface
	CoInitialize(NULL);

	//Start the Excel Application
	XL.CreateInstance(L"Excel.Application");

	//Make the Excel Application visible, so that we can see it!
	XL->Visible[0] = false;

	return;
}

void IOExcel::Open_Workbook(std::string &s)
{
	file_name = s;
	XL->Workbooks->Open(file_name.c_str());
	XL->PutDisplayAlerts(LOCALE_USER_DEFAULT, VARIANT_FALSE);

	pSheet = XL->ActiveSheet;
	pRange = pSheet->Cells;

	return;
}

int IOExcel::Find_Project(std::string &s)
{
	for (int i = 3; i < 18; i++)
	{
		_bstr_t bstr = pRange->Item[i][1];
		std::string str = bstr;

		if (str.length() == 0)
		{
			return i;
		}
		if (s == str)
		{
			return i;
		}
	}
	return 3;
}

void IOExcel::Save_Workbook()
{
	try
	{
		pSheet->SaveAs(file_name.c_str(), Excel::xlOpenXMLWorkbook, vtMissing,
			vtMissing, vtMissing, vtMissing, Excel::xlNoChange);
	}
	catch (_com_error &err)
	{
		wprintf(L"Excel throws the error: %s\n", err.ErrorMessage());
		wprintf(L"Description: %s\n", (LPCWSTR)err.Description());
	}
	return;
}

void IOExcel::Write_Double(int row, int col, double val)
{
	double d = pRange->Item[row][col];

	d += val;
	pRange->Item[row][col] = d;
	return;
}

void IOExcel::Write_String(int row, int col, std::string val)
{
	_bstr_t bstr = val.c_str();
	pRange->Item[row][col] = bstr;
	return;
}

