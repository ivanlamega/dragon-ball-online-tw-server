CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 300;
	title = 30002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
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
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 30009;
				ctype = 1;
				idx = 6312101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 30008;
				m1fx = "5359.000000";
				area = 30001;
				goal = 30004;
				m0fz = "-2289.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 30016;
				sort = 30005;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-1944.000000";
				grade = 132203;
				m0fx = "5119.000000";
				m0ttip = 30015;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 30002;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 1;
				idx0 = 488;
				cnt0 = 8;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 489;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 30008;
			gtype = 2;
			oklnk = 2;
			area = 30001;
			goal = 30004;
			sort = 30005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 30002;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 30014;
			nextlnk = 101;
			rwdtbl = 30001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312101;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 30007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6312101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 23;
				minlvl = 15;
			}
			CDboTSCheckClrQst
			{
				and = "292;";
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iidx1 = 489;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 488;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
	}
}

