CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 239;
	title = 23902;

	CNtlTSGroup
	{
		gid = 0;

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
			stdiag = 23907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 5533401;
			}
			CDboTSCheckLvl
			{
				maxlvl = 16;
				minlvl = 8;
			}
			CDboTSCheckClrQst
			{
				or = "237;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 23908;
			gtype = 3;
			oklnk = 2;
			area = 23901;
			goal = 23904;
			sort = 23905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 23902;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 23908;
				m1fx = "4057.000000";
				area = 23901;
				goal = 23904;
				m0fz = "-3198.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 23916;
				sort = 23905;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-3254.000000";
				grade = 132203;
				m0fx = "4106.000000";
				m0ttip = 23915;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 23902;
				gtype = 3;
			}
			CDboTSActNPCConv
			{
				conv = 23909;
				ctype = 1;
				idx = 5533401;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 0;
				idx0 = 1512106;
				cnt0 = 5;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 1512104;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
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
				eitype = 0;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 23914;
			nextlnk = 101;
			rwdtbl = 23901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5533401;
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
				itype = 0;
			}
		}
	}
}

