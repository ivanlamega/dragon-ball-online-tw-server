CNtlTSTrigger
{
	sm = 0;
	sq = 1;
	rq = 0;
	tid = 11627;
	title = 1100733;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "38;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 38;
			elnk = 255;
			nextlnk = 254;
			prelnk = "36;34;32;30;28;26;";

			CDboTSActSendSvrEvt
			{
				id = 17040;
				tblidx = -1;
				stradius = 0;
				stype = 0;
				taid = 1;
				ttype = 0;
				type = 5;
			}
		}
		CDboTSContGCond
		{
			cid = 37;
			prelnk = "36;34;32;30;28;26;";
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1701101;
			}
		}
		CDboTSContNarration
		{
			cancellnk = 9;
			cid = 8;
			dt = 2;
			lilnk = 255;
			oklnk = 9;
			ot = 0;
			pt = 2;
			mlt = 10000;
			os = 1;
			prelnk = "7;";
			dg = 1100741;
			gt = 0;
			oi = 1701101;
		}
		CDboTSContGCond
		{
			cid = 31;
			prelnk = "29;";
			nolnk = 33;
			rm = 0;
			yeslnk = 32;

			CDboTSCheckPCCls
			{
				clsflg = 24584;
			}
		}
		CDboTSContGCond
		{
			cid = 29;
			prelnk = "27;";
			nolnk = 31;
			rm = 0;
			yeslnk = 30;

			CDboTSCheckPCCls
			{
				clsflg = 98320;
			}
		}
		CDboTSContGCond
		{
			cid = 27;
			prelnk = "25;";
			nolnk = 29;
			rm = 0;
			yeslnk = 28;

			CDboTSCheckPCCls
			{
				clsflg = 385;
			}
		}
		CDboTSContReward
		{
			canclnk = 37;
			cid = 32;
			didx0 = 320311;
			dval0 = 0;
			desc = 1100765;
			nextlnk = 38;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 3;
			ltime = -1;
			prelnk = "31;";
			usetbl = 0;
		}
		CDboTSContReward
		{
			canclnk = 37;
			cid = 30;
			didx0 = 420411;
			dval0 = 0;
			desc = 1100765;
			nextlnk = 38;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 3;
			ltime = -1;
			prelnk = "29;";
			usetbl = 0;
		}
		CDboTSContReward
		{
			canclnk = 37;
			cid = 28;
			didx0 = 20211;
			dval0 = 0;
			desc = 1100765;
			nextlnk = 38;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 3;
			ltime = -1;
			prelnk = "27;";
			usetbl = 0;
		}
		CDboTSContGCond
		{
			cid = 25;
			prelnk = "9;";
			nolnk = 27;
			rm = 0;
			yeslnk = 26;

			CDboTSCheckPCCls
			{
				clsflg = 1538;
			}
		}
		CDboTSContGCond
		{
			cid = 33;
			prelnk = "31;";
			nolnk = 35;
			rm = 0;
			yeslnk = 34;

			CDboTSCheckPCCls
			{
				clsflg = 393248;
			}
		}
		CDboTSContGCond
		{
			cid = 35;
			prelnk = "33;";
			nolnk = 255;
			rm = 0;
			yeslnk = 36;

			CDboTSCheckPCCls
			{
				clsflg = 1572928;
			}
		}
		CDboTSContGAct
		{
			cid = 9;
			elnk = 255;
			nextlnk = 25;
			prelnk = "8;8;7;6;5;4;3;2;1;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 1000;
			}
		}
		CDboTSContReward
		{
			canclnk = 37;
			cid = 26;
			didx0 = 120311;
			dval0 = 0;
			desc = 1100765;
			nextlnk = 38;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 3;
			ltime = -1;
			prelnk = "25;";
			usetbl = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 1100732;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1701101;
			}
			CDboTSCheckClrQst
			{
				and = "11626;";
			}
		}
		CDboTSContReward
		{
			canclnk = 37;
			cid = 34;
			didx0 = 520321;
			dval0 = 0;
			desc = 1100765;
			nextlnk = 38;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 3;
			ltime = -1;
			prelnk = "33;";
			usetbl = 0;
		}
		CDboTSContReward
		{
			canclnk = 37;
			cid = 36;
			didx0 = 620151;
			dval0 = 0;
			desc = 1100765;
			nextlnk = 38;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 3;
			ltime = -1;
			prelnk = "35;";
			usetbl = 0;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;";
			type = 0;
		}
		CDboTSContNarration
		{
			cancellnk = 9;
			cid = 7;
			dt = 2;
			lilnk = 255;
			oklnk = 8;
			ot = 2;
			pt = 2;
			mlt = 10000;
			os = 0;
			prelnk = "6;";
			dg = 1100740;
			gt = 0;
			oi = -1;
		}
		CDboTSContNarration
		{
			cancellnk = 9;
			cid = 6;
			dt = 2;
			lilnk = 255;
			oklnk = 7;
			ot = 0;
			pt = 1;
			mlt = 10000;
			os = 1;
			prelnk = "5;";
			dg = 1100739;
			gt = 0;
			oi = 1701101;
		}
		CDboTSContNarration
		{
			cancellnk = 9;
			cid = 5;
			dt = 2;
			lilnk = 255;
			oklnk = 6;
			ot = 2;
			pt = 1;
			mlt = 10000;
			os = 0;
			prelnk = "4;";
			dg = 1100738;
			gt = 0;
			oi = -1;
		}
		CDboTSContNarration
		{
			cancellnk = 9;
			cid = 4;
			dt = 2;
			lilnk = 255;
			oklnk = 5;
			ot = 0;
			pt = 1;
			mlt = 10000;
			os = 1;
			prelnk = "3;";
			dg = 1100737;
			gt = 0;
			oi = 1701101;
		}
		CDboTSContNarration
		{
			cancellnk = 9;
			cid = 3;
			dt = 2;
			lilnk = 255;
			oklnk = 4;
			ot = 0;
			pt = 1;
			mlt = 10000;
			os = 1;
			prelnk = "2;";
			dg = 1100736;
			gt = 0;
			oi = 1701101;
		}
		CDboTSContNarration
		{
			cancellnk = 9;
			cid = 2;
			dt = 2;
			lilnk = 255;
			oklnk = 3;
			ot = 2;
			pt = 0;
			mlt = 10000;
			os = 0;
			prelnk = "1;";
			dg = 1100735;
			gt = 0;
			oi = -1;
		}
		CDboTSContNarration
		{
			cancellnk = 9;
			cid = 1;
			dt = 2;
			lilnk = 255;
			oklnk = 2;
			ot = 0;
			pt = 0;
			mlt = 10000;
			os = 1;
			prelnk = "37;0;";
			dg = 1100734;
			gt = 0;
			oi = 1701101;
		}
	}
}

