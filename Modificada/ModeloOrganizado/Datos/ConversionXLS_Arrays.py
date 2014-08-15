# -*- coding: utf-8 -*-

from xlrd import open_workbook
from string import *

def main():

    nameWorkBook=input("Type the name of the workbook without ext.")
    nameOutputFileTTCN3=input("Type the name of the output ttcn3 without ext")

    ArrayData=getData(nameWorkBook)
    conversion2TTCN3(ArrayData,nameOutputFileTTCN3)

def getData(nFile):

    filename = nFile+".xls"
    book = open_workbook(filename)
    sheet_index = 1 #Se empieza desde la hoja ENTRADA Hasta la Hoja CONSOLIDADO
    total=[]

    ###constants definitions###
    zone0=0
    zone1=1
    ctrl0=0
    ctrl1=1
    dataBook=[]
    for sheet_index in range(1,4):
        sheet=book.sheet_by_index(sheet_index)
        row_index = 1
        valueWholeSheet = []
        for row_index in range(sheet.nrows):
            col_index=0
            for col_index in range(sheet.ncols):


                if (row_index>0):
                    valueTuple=[]
                    if ( col_index==3 ):
                        valueTuple.append(sheet.cell(row_index,col_index).value)
                        valueTuple.append(ctrl0)
                        valueTuple.append(zone0)
                        valueWholeSheet.append(valueTuple)
                    elif ( col_index==4 ):
                        valueTuple.append(sheet.cell(row_index,col_index).value)
                        valueTuple.append(ctrl0)
                        valueTuple.append(zone1)
                        valueWholeSheet.append(valueTuple)
                    elif ( col_index==5 ):
                        valueTuple.append(sheet.cell(row_index,col_index).value)
                        valueTuple.append(ctrl1)
                        valueTuple.append(zone0)
                        valueWholeSheet.append(valueTuple)
                    elif ( col_index==6 ):
                        valueTuple.append(sheet.cell(row_index,col_index).value)
                        valueTuple.append(ctrl1)
                        valueTuple.append(zone1)
                        valueWholeSheet.append(valueTuple)
        dataBook.append(valueWholeSheet)
    return dataBook

def conversion2TTCN3(dataWorkBook,nameTTCN3):

    ###CONSTANTS###
    nameArrays_TTCN3=['aEntryCars2Zone','aOutCars2Zone','aFreeSpotsExpecInZone']
    Length_Vec_Datas=len(dataWorkBook)
    Length_Rows_Vec=len(dataWorkBook[0])
    i=0

    #Creation of file *.ttcn3#
    nameFileTTCN3=nameTTCN3+".ttcn3"
    fileTTCN3=open(nameFileTTCN3,'w')

    #Creation of type array in TTCN-3#
    fileTTCN3.write("/*These are the definitions of the array*/\n")
    fileTTCN3.write("type integer generic_array_data["+str(Length_Rows_Vec)+
                    "][3];\n")
    
    for i in range(len(dataWorkBook)):
        data=dataWorkBook[i]
        dataStr=str(data).replace("[","{")
        dataStr=dataStr.replace("]","}")
        dataStr=dataStr.replace(".0","")
        fileTTCN3.write("const generic_array_data "+nameArrays_TTCN3[i]+
                        ":="+dataStr+";\n")
        
                

    fileTTCN3.close()

#called to main function:
main()
