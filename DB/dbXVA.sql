/*
Navicat SQLite Data Transfer

Source Server         : XVA
Source Server Version : 30802
Source Host           : :0

Target Server Type    : SQLite
Target Server Version : 30802
File Encoding         : 65001

Date: 2014-12-10 09:24:34
*/

PRAGMA foreign_keys = OFF;

-- ----------------------------
-- Table structure for CalculateNettingSet
-- ----------------------------
DROP TABLE IF EXISTS "main"."CalculateNettingSet";
CREATE TABLE "CalculateNettingSet" ("id" INTEGER PRIMARY KEY  NOT NULL , "netting_set" TEXT NOT NULL );

-- ----------------------------
-- Table structure for Colateral
-- ----------------------------
DROP TABLE IF EXISTS "main"."Colateral";
CREATE TABLE "Colateral" (
	 "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	 "netting_set" TEXT NOT NULL,
	 "num_operacion" TEXT NOT NULL,
	 "num_simulacion" INTEGER NOT NULL,
	 "tiempo" FLOAT NOT NULL,
	 "valor" FLOAT NOT NULL
);

-- ----------------------------
-- Table structure for Curva
-- ----------------------------
DROP TABLE IF EXISTS "main"."Curva";
CREATE TABLE "Curva" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT NOT NULL , "plazo" REAL NOT NULL , "valor" REAL NOT NULL );

-- ----------------------------
-- Table structure for CustomAmortization
-- ----------------------------
DROP TABLE IF EXISTS "main"."CustomAmortization";
CREATE TABLE "CustomAmortization" ("Id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "deal_number" INTEGER NOT NULL REFERENCES "Operacion" ("id") ON DELETE RESTRICT ON UPDATE RESTRICT, "amort_time" INTEGER NOT NULL, "amort_percent" REAL NOT NULL, "leg" TEXT NOT NULL);

-- ----------------------------
-- Table structure for DealNumberNettingSet
-- ----------------------------
DROP TABLE IF EXISTS "main"."DealNumberNettingSet";
CREATE TABLE "DealNumberNettingSet" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "deal_number" TEXT NOT NULL , "netting_set" TEXT NOT NULL );

-- ----------------------------
-- Table structure for ExposureMetrics
-- ----------------------------
DROP TABLE IF EXISTS "main"."ExposureMetrics";
CREATE TABLE "ExposureMetrics" (
	 "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	 "netting_set" text NOT NULL,
	 "stop_time" INTEGER NOT NULL,
	 "expected_exposure" DOUBLE NOT NULL,
	 "negative_expected_exposure" DOUBLE NOT NULL,
	 "max_exposure" DOUBLE NOT NULL,
	 "potential_future_exposure" DOUBLE NOT NULL,
	 "expected_future_value" DOUBLE NOT NULL
);

-- ----------------------------
-- Table structure for Fx
-- ----------------------------
DROP TABLE IF EXISTS "main"."Fx";
CREATE TABLE "Fx" (
	 "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	 "nombre" TEXT NOT NULL,
	 "valor" REAL NOT NULL,
	 "curva_fuerte" TEXT,
	 "curva_debil" TEXT
);

-- ----------------------------
-- Table structure for FxBase
-- ----------------------------
DROP TABLE IF EXISTS "main"."FxBase";
CREATE TABLE "FxBase" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "moneda_base" TEXT NOT NULL );

-- ----------------------------
-- Table structure for Gamma
-- ----------------------------
DROP TABLE IF EXISTS "main"."Gamma";
CREATE TABLE "Gamma" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT NOT NULL , "valor" REAL NOT NULL );

-- ----------------------------
-- Table structure for Institution
-- ----------------------------
DROP TABLE IF EXISTS "main"."Institution";
CREATE TABLE "Institution" ("id" INTEGER PRIMARY KEY  NOT NULL ,"default_prob" DOUBLE NOT NULL  DEFAULT (0) ,"recovery_rate" DOUBLE NOT NULL  DEFAULT (0) , "spread_cap" DOUBLE NOT NULL  DEFAULT 0, "spread_col" DOUBLE NOT NULL  DEFAULT 0);

-- ----------------------------
-- Table structure for NettingSet
-- ----------------------------
DROP TABLE IF EXISTS "main"."NettingSet";
CREATE TABLE "NettingSet" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT, "recovery_rate" DOUBLE, "default_prob" DOUBLE, "threshold_curr" TEXT, "threshold_ns" INTEGER, "threshold_inst" INTEGER, "periodicity" INTEGER, "collateral_adjustment" REAL DEFAULT null, "mta" REAL DEFAULT null);

-- ----------------------------
-- Table structure for NettingSet_old_20140924
-- ----------------------------
DROP TABLE IF EXISTS "main"."NettingSet_old_20140924";
CREATE TABLE "NettingSet_old_20140924" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT, "recovery_rate" DOUBLE, "default_prob" DOUBLE, "threshold_curr" TEXT, "threshold_ns" INTEGER, "threshold_inst" INTEGER, "periodicity" INTEGER);

-- ----------------------------
-- Table structure for Operacion
-- ----------------------------
DROP TABLE IF EXISTS "main"."Operacion";
CREATE TABLE "Operacion" (
	 "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	 "deal_number" TEXT NOT NULL,
	 "type" TEXT NOT NULL,
	 "pricer" TEXT NOT NULL,
	 "fx" TEXT,
	 "bStartTime" DOUBLE NOT NULL,
	 "bExpiryTime" DOUBLE NOT NULL,
	 "bCurrency" TEXT NOT NULL,
	 "bAmount" DOUBLE NOT NULL,
	 "bTipoTasa" TEXT NOT NULL,
	 "bFormaTasa" TEXT NOT NULL,
	 "bValueRate" real NOT NULL,
	 "bPeriodicity" text NOT NULL,
	 "bStubPeriod" text NOT NULL,
	 "bFixPeriodicity" text,
	 "bFixStubPeriod" text,
	 "bSpread" real,
	 "bAmort" real NOT NULL,
	 "bIncludeAmort" text NOT NULL,
	 "bProjCurve" TEXT,
	 "bDiscountCurve" TEXT NOT NULL,
	 "bInitialUF" real,
	 "sStartTime" DOUBLE NOT NULL,
	 "sExpiryTime" DOUBLE NOT NULL,
	 "sCurrency" TEXT NOT NULL,
	 "sAmount" DOUBLE NOT NULL,
	 "sTipoTasa" TEXT NOT NULL,
	 "sFormaTasa" TEXT NOT NULL,
	 "sValueRate" real NOT NULL,
	 "sPeriodicity" text NOT NULL,
	 "sStubPeriod" text NOT NULL,
	 "sFixPeriodicity" text,
	 "sFixStubPeriod" text,
	 "sSpread" real,
	 "sAmort" real NOT NULL,
	 "sIncludeAmort" text NOT NULL,
	 "sProjCurve" TEXT,
	 "sDiscountCurve" TEXT NOT NULL,
	 "sInitialUF" real
);

-- ----------------------------
-- Table structure for ParamValorizacion
-- ----------------------------
DROP TABLE IF EXISTS "main"."ParamValorizacion";
CREATE TABLE "ParamValorizacion" (
"id"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"netting_set"  TEXT NOT NULL,
"se_valoriza"  TEXT NOT NULL
);

-- ----------------------------
-- Table structure for Rho
-- ----------------------------
DROP TABLE IF EXISTS "main"."Rho";
CREATE TABLE "Rho" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT NOT NULL , "valor" REAL NOT NULL );

-- ----------------------------
-- Table structure for Sigma
-- ----------------------------
DROP TABLE IF EXISTS "main"."Sigma";
CREATE TABLE "Sigma" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT NOT NULL , "valor" REAL NOT NULL );

-- ----------------------------
-- Table structure for Simulacion
-- ----------------------------
DROP TABLE IF EXISTS "main"."Simulacion";
CREATE TABLE "Simulacion" ("id" INTEGER PRIMARY KEY  NOT NULL ,"factor" TEXT NOT NULL ,"num_simulacion" INTEGER NOT NULL ,"tiempo" INTEGER NOT NULL  DEFAULT (null) ,"valor" DOUBLE NOT NULL );

-- ----------------------------
-- Table structure for sqlite_sequence
-- ----------------------------
DROP TABLE IF EXISTS "main"."sqlite_sequence";
CREATE TABLE sqlite_sequence(name,seq);

-- ----------------------------
-- Table structure for StopTimesParaValorizacion
-- ----------------------------
DROP TABLE IF EXISTS "main"."StopTimesParaValorizacion";
CREATE TABLE "StopTimesParaValorizacion" (
"id"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"stopping_time"  INTEGER NOT NULL
);

-- ----------------------------
-- Table structure for test
-- ----------------------------
DROP TABLE IF EXISTS "main"."test";
CREATE TABLE "test" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , "campo1" TEXT, "campo2" REAL);

-- ----------------------------
-- Table structure for TipoAmortizacion
-- ----------------------------
DROP TABLE IF EXISTS "main"."TipoAmortizacion";
CREATE TABLE "TipoAmortizacion" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT NOT NULL  UNIQUE );

-- ----------------------------
-- Table structure for Valorizacion
-- ----------------------------
DROP TABLE IF EXISTS "main"."Valorizacion";
CREATE TABLE "Valorizacion" (
	 "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	 "netting_set" TEXT NOT NULL,
	 "num_operacion" TEXT NOT NULL,
	 "num_simulacion" INTEGER NOT NULL,
	 "tiempo" FLOAT NOT NULL,
	 "valor" FLOAT NOT NULL
);

-- ----------------------------
-- Table structure for ValorPercentil
-- ----------------------------
DROP TABLE IF EXISTS "main"."ValorPercentil";
CREATE TABLE "ValorPercentil" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "valor" DOUBLE NOT NULL );

-- ----------------------------
-- Table structure for Xva
-- ----------------------------
DROP TABLE IF EXISTS "main"."Xva";
CREATE TABLE "Xva" (
"id"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"netting_set"  TEXT NOT NULL,
"unilateral_cva"  DOUBLE NOT NULL,
"value_cva"  DOUBLE NOT NULL,
"unilateral_dva"  DOUBLE,
"value_dva"  DOUBLE NOT NULL,
"bilateral_cva"  DOUBLE NOT NULL,
"value_fva"  DOUBLE NOT NULL,
"value_pfe_max"  DOUBLE NOT NULL,
"value_epe"  DOUBLE NOT NULL
);