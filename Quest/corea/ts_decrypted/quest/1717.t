CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1717;
	title = 171702;

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
				conv = 171709;
				ctype = 1;
				idx = 5041115;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 171708;
				gtype = 1;
				area = 171701;
				goal = 171704;
				grade = 132203;
				rwd = 100;
				sort = 171705;
				stype = 2;
				taid = 1;
				title = 171702;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 171708;
			gtype = 1;
			oklnk = 2;
			area = 171701;
			goal = 171704;
			sort = 171705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 171702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 171714;
			nextlnk = 254;
			rwdtbl = 171701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6311102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 171707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5041115;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1716;";
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
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

