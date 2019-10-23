CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 217;
	title = 21702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 21709;
				ctype = 1;
				idx = 4211101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 21708;
				gtype = 1;
				area = 21701;
				goal = 21704;
				grade = 132203;
				rwd = 100;
				sort = 21705;
				stype = 1;
				taid = 1;
				title = 21702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 21707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 16;
			}
			CDboTSClickNPC
			{
				npcidx = 4211101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 12;
				minlvl = 4;
			}
			CDboTSCheckClrQst
			{
				or = "204;";
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 21708;
			gtype = 1;
			oklnk = 2;
			area = 21701;
			goal = 21704;
			sort = 21705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 21702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 21714;
			nextlnk = 254;
			rwdtbl = 21701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751101;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

