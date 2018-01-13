object FrmAbout: TFrmAbout
  Left = 195
  Top = 79
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Se'#231#227'o finalizada'
  ClientHeight = 313
  ClientWidth = 267
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 50
    Top = 242
    Width = 160
    Height = 16
    Caption = 'Se'#231#227'o eleitoral finalizada!!!'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object btnSair: TBitBtn
    Left = 88
    Top = 266
    Width = 80
    Height = 40
    TabOrder = 0
    OnClick = btnSairClick
    Kind = bkOK
  end
  object mmAbout: TMemo
    Left = 0
    Top = 8
    Width = 265
    Height = 221
    BevelKind = bkFlat
    BevelOuter = bvRaised
    Color = cl3DLight
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'Desenvolvimento:'
      ''
      '             Douglas Chagas da Silva'
      '             Heder Dorneles Soares'
      '             Rodolfo Medeiros Trinetto'
      ''
      'Vers'#227'o 1.0'
      'Copyhight (c) 2006'
      'Ferramenta: Borland C++Builder6'
      ''
      'Ci'#234'ncia da Computa'#231#227'o UFT'
      'Mat'#233'ria: Programa'#231#227'o Avan'#231'ada'
      'Problema das Elei'#231#245'es'
      'Professor: George Brito')
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
end
