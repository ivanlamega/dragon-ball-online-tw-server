CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6005;
	title = 600502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 8;
			prelnk = "7;";
			nolnk = 106;
			rm = 0;
			yeslnk = 105;

			CDboTSCheckPCCls
			{
				clsflg = 32;
			}
		}
		CDboTSContGCond
		{
			cid = 7;
			prelnk = "6;";
			nolnk = 8;
			rm = 0;
			yeslnk = 104;

			CDboTSCheckPCCls
			{
				clsflg = 16;
			}
		}
		CDboTSContGCond
		{
			cid = 6;
			prelnk = "5;";
			nolnk = 7;
			rm = 0;
			yeslnk = 103;

			CDboTSCheckPCCls
			{
				clsflg = 8;
			}
		}
		CDboTSContGCond
		{
			cid = 16;
			prelnk = "106;";
			nolnk = 255;
			rm = 1;
			yeslnk = 106;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContGCond
		{
			cid = 15;
			prelnk = "105;";
			nolnk = 255;
			rm = 1;
			yeslnk = 105;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContGCond
		{
			cid = 11;
			prelnk = "101;";
			nolnk = 255;
			rm = 1;
			yeslnk = 101;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContGCond
		{
			cid = 12;
			prelnk = "102;";
			nolnk = 255;
			rm = 1;
			yeslnk = 102;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContReward
		{
			didx3 = 632011;
			dval3 = 1;
			nextlnk = 200;
			rwdtype = 0;
			didx2 = -1;
			dtype0 = 2;
			dval2 = 0;
			ltime = -1;
			prelnk = "8;16;";
			usetbl = 0;
			didx1 = -1;
			dtype1 = 4;
			dval1 = 195;
			canclnk = 16;
			cid = 106;
			didx0 = -1;
			dtype2 = 9;
			dval0 = 1600;
			desc = 600514;
			dtype3 = 3;
			rwdtbl = 600501;
		}
		CDboTSContGCond
		{
			cid = 5;
			prelnk = "4;";
			nolnk = 6;
			rm = 0;
			yeslnk = 102;

			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
		}
		CDboTSContReward
		{
			didx3 = 532011;
			dval3 = 1;
			nextlnk = 200;
			rwdtype = 0;
			didx2 = -1;
			dtype0 = 2;
			dval2 = 0;
			ltime = -1;
			prelnk = "8;15;";
			usetbl = 0;
			didx1 = -1;
			dtype1 = 4;
			dval1 = 195;
			canclnk = 15;
			cid = 105;
			didx0 = -1;
			dtype2 = 9;
			dval0 = 1600;
			desc = 600514;
			dtype3 = 3;
			rwdtbl = 600501;
		}
		CDboTSContGCond
		{
			cid = 14;
			prelnk = "104;";
			nolnk = 255;
			rm = 1;
			yeslnk = 104;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContReward
		{
			didx3 = 430411;
			dval3 = 1;
			nextlnk = 200;
			rwdtype = 0;
			didx2 = -1;
			dtype0 = 2;
			dval2 = 0;
			ltime = -1;
			prelnk = "7;14;";
			usetbl = 0;
			didx1 = -1;
			dtype1 = 4;
			dval1 = 195;
			canclnk = 14;
			cid = 104;
			didx0 = -1;
			dtype2 = 9;
			dval0 = 1600;
			desc = 600514;
			dtype3 = 3;
			rwdtbl = 600501;
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 5;
			rm = 0;
			yeslnk = 101;

			CDboTSCheckPCCls
			{
				clsflg = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 13;
			prelnk = "103;";
			nolnk = 255;
			rm = 1;
			yeslnk = 103;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "201;";
			type = 1;
		}
		CDboTSContGCond
		{
			cid = 201;
			prelnk = "200;";
			nolnk = 100;
			rm = 1;
			yeslnk = 253;

			CDboTSCheckProgQuest
			{
				qid = 6005;
			}
		}
		CDboTSContReward
		{
			didx3 = 30611;
			dval3 = 1;
			nextlnk = 200;
			rwdtype = 0;
			didx2 = -1;
			dtype0 = 2;
			dval2 = 0;
			ltime = -1;
			prelnk = "4;11;";
			usetbl = 0;
			didx1 = -1;
			dtype1 = 4;
			dval1 = 195;
			canclnk = 11;
			cid = 101;
			didx0 = -1;
			dtype2 = 9;
			dval0 = 1600;
			desc = 600514;
			dtype3 = 3;
			rwdtbl = 600501;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;0;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 600509;
				ctype = 1;
				idx = 3551101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 600508;
				gtype = 1;
				area = 600501;
				goal = 600504;
				grade = -1;
				rwd = 100;
				sort = 600505;
				stype = 0;
				taid = 1;
				title = 600502;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
				idx0 = 620;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			didx3 = 330611;
			dval3 = 1;
			nextlnk = 200;
			rwdtype = 0;
			didx2 = -1;
			dtype0 = 2;
			dval2 = 0;
			ltime = -1;
			prelnk = "6;13;";
			usetbl = 0;
			didx1 = -1;
			dtype1 = 4;
			dval1 = 195;
			canclnk = 13;
			cid = 103;
			didx0 = -1;
			dtype2 = 9;
			dval0 = 1600;
			desc = 600514;
			dtype3 = 3;
			rwdtbl = 600501;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 600507;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckClrQst
			{
				and = "6004;";
			}
			CDboTSClickNPC
			{
				npcidx = 3551101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
		}
		CDboTSContReward
		{
			didx3 = 130411;
			dval3 = 1;
			nextlnk = 200;
			rwdtype = 0;
			didx2 = -1;
			dtype0 = 2;
			dval2 = 0;
			ltime = -1;
			prelnk = "5;12;";
			usetbl = 0;
			didx1 = -1;
			dtype1 = 4;
			dval1 = 195;
			canclnk = 12;
			cid = 102;
			didx0 = -1;
			dtype2 = 9;
			dval0 = 1600;
			desc = 600514;
			dtype3 = 3;
			rwdtbl = 600501;
		}
		CDboTSContGAct
		{
			cid = 200;
			elnk = 255;
			nextlnk = 201;
			prelnk = "106;105;104;103;102;101;";

			CDboTSActQItem
			{
				icnt0 = 1;
				iprob0 = "1.000000";
				iidx0 = 620;
				taid = 2;
				type = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 600508;
			gtype = 1;
			oklnk = 2;
			area = 600501;
			goal = 600504;
			sort = 600505;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 600502;
		}
		CDboTSContReward
		{
			desc = 600514;
			nextlnk = 255;
			rwdtbl = 600501;
			rwdtype = 0;
			didx2 = -1;
			dtype0 = 2;
			dval2 = 0;
			ltime = -1;
			prelnk = "201;";
			usetbl = 0;
			didx1 = -1;
			dtype1 = 4;
			dval1 = 195;
			canclnk = 255;
			cid = 100;
			didx0 = -1;
			dtype2 = 9;
			dval0 = 1600;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 620;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 3;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 620;
			}
		}
		CDboTSContEnd
		{
			cid = 3;
			prelnk = "2;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

