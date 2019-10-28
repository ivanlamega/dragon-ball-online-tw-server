CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1450;
	title = 145002;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 145007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2803101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSCheckClrQst
			{
				and = "1409;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 145009;
				ctype = 1;
				idx = 2803101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 145008;
				m1fx = "1280.000000";
				area = 145001;
				goal = 145004;
				m0fz = "56.000000";
				m0widx = 2;
				m1fy = "0.000000";
				m1ttip = 145016;
				sort = 145005;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "56.000000";
				grade = 132203;
				m0fx = "1280.000000";
				m0ttip = 145015;
				m1widx = 2;
				rwd = 100;
				taid = 1;
				title = 145002;
				gtype = 4;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 1;
				idx0 = 1017;
				cnt0 = 4;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 1016;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 145008;
			gtype = 4;
			oklnk = 2;
			area = 145001;
			goal = 145004;
			sort = 145005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 145002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 145014;
			nextlnk = 101;
			rwdtbl = 145001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2803101;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 1016;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 4;
				iidx = 1017;
			}
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
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 145007;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iidx1 = 1017;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 1016;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
	}
}

