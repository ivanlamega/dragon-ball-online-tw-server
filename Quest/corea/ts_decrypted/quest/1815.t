CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1815;
	title = 181502;

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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 181507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5312105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 41;
				minlvl = 33;
			}
			CDboTSCheckClrQst
			{
				and = "1813;";
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
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 181509;
				ctype = 1;
				idx = 5312105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 181508;
				gtype = 2;
				area = 181501;
				goal = 181504;
				m0fz = "-197.000000";
				m0widx = 1;
				sort = 181505;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "4185.000000";
				m0ttip = 181515;
				rwd = 100;
				taid = 1;
				title = 181502;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 1096;
				cnt0 = 18;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 181508;
			gtype = 2;
			oklnk = 2;
			area = 181501;
			goal = 181504;
			sort = 181505;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 181502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 181514;
			nextlnk = 101;
			rwdtbl = 181501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5312105;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 18;
				iidx = 1096;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

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
				iprob0 = "1.000000";
				iidx0 = 1096;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 181507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

